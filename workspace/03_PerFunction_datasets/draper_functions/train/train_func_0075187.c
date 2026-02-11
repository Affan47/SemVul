nscrlup(SCRN *t, int top, int bot, int amnt)
{
	int x;

	if (!amnt || top >= bot || bot > t->li)
		return;
	if ((amnt < bot - top && bot - top - amnt < amnt / 2) || !t->scroll)
		amnt = bot - top;
	if (amnt < bot - top) {
		for (x = top + amnt; x != bot; ++x) {
			t->sary[x - amnt] = (t->sary[x] == t->li ? t->li : t->sary[x] + amnt);
			t->updtab[x - amnt] = t->updtab[x];
		}
		for (x = bot - amnt; x != bot; ++x) {
			t->updtab[x] = 1;
		}
	}
	if (amnt > bot - top)
		amnt = bot - top;
	msetI(t->sary + bot - amnt, t->li, amnt);
	if (amnt == bot - top) {
		msetI(t->updtab + bot - amnt, 1, amnt);
		}
}
