umpgup(MENU *m)
{
	int amnt = (m->h+1)/2;
	if (m->top >= amnt*m->perline) {
		m->top -= amnt*m->perline;
		m->cursor -= amnt*m->perline;
		return 0;
	} else if (m->top) {
		m->cursor -= m->top;
		m->top = 0;
		return 0;
	} else if (m->cursor >= m->perline) {
		m->cursor = m->cursor % m->perline;
		return 0;
	} else
		return -1;
}
