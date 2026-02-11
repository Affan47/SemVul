find_menu(unsigned char *s)
{
	struct rc_menu *m;
	for (m = menus; m; m = m->next)
		if (!zcmp(m->name, s))
			break;
	return m;
}
