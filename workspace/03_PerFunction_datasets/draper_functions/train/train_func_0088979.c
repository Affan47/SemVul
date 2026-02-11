eraeol(SCRN *t, int x, int y)
{
	int *s, *ss, *a, *aa;
	int w = t->co - x - 1;

	if (w <= 0)
		return 0;
	s = t->scrn + y * t->co + x;
	a = t->attr + y * t->co + x;
	ss = s + w;
	aa = a + w;
	do {
		if (*--ss != ' ') {
			++ss;
			break;
		} else if (*--aa != 0) {
			++ss;
			++aa;
			break;
		}
	} while (ss != s);
	if ((ss - s > 3 || s[w] != ' ' || a[w] != 0) && t->ce) {
		cpos(t, x, y);
		set_attr(t, 0);
		texec(t->cap, t->ce, 1, 0, 0, 0, 0);
		msetI(s, ' ', w);
		msetI(a, 0, w);
	} else if (s != ss) {
		if (t->ins)
			clrins(t);
		if (t->x != x || t->y != y)
			cpos(t, x, y);
		if (t->attrib)
			set_attr(t, 0);
		while (s != ss) {
			*s = ' ';
			*a = 0;
			ttputc(' ');
			++t->x;
			++s;
			++a;
		}
	}
	return 0;
}
