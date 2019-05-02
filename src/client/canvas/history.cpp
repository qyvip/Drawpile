/*
   Drawpile - a collaborative drawing program.

   Copyright (C) 2008-2019 Calle Laakkonen

   Drawpile is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Drawpile is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Drawpile.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "history.h"
#include "../shared/net/undo.h"

namespace canvas {

using namespace protocol;

History::History()
	: m_offset(0), m_bytes(0)
{
}

void History::append(MessagePtr msg)
{
	m_messages.append(msg);
	m_bytes += msg->length();
}

void History::cleanup(int indexlimit)
{
	Q_ASSERT(indexlimit <= end());

	while(m_offset < indexlimit) {
		m_bytes -= m_messages.takeFirst()->length();
		++m_offset;
	}
}

void History::resetTo(int newoffset)
{
	Q_ASSERT(newoffset >= 0);
	m_offset = newoffset;
	m_messages.clear();
	m_bytes = 0;
}

}
