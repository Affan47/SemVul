umuparw(MENU *m)
{
	if (m->cursor >= m->perline) {
		m->cursor -= m->perline;
		return 0;
	} else
		return -1;
}
