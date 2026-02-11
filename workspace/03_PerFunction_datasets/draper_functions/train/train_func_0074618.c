umbacks(MENU *m)
{
	if (m->backs)
		return m->backs(m, m->cursor, m->object);
	else
		return -1;
}
