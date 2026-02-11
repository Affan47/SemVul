umrtarw(MENU *m)
{
	if (transpose) {
		int cut = m->nitems % m->lines;
		if (!cut) cut = m->lines;
		if (m->cursor % m->lines >= cut) {
			if (m->cursor / m->lines != m->perline - 2) {
				m->cursor += m->lines;
				return 0;
			}
		} else {
			if (m->cursor / m->lines != m->perline - 1) {
				m->cursor += m->lines;
				return 0;
			}
		}
		if ((m->cursor % m->lines) + 1 < m->lines) {
			m->cursor = m->cursor % m->lines + 1;
			return 0;
		}
		return -1;
	} else if (m->cursor + 1 < m->nitems) {
		++m->cursor;
		return 0;
	} else
		return -1;
}
