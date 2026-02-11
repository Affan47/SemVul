nredraw(SCRN *t)
{
	dostaupd = 1;
	msetI(t->scrn, ' ', t->co * skiptop);
	msetI(t->attr, BG_COLOR(bg_text), t->co * skiptop);
	msetI(t->scrn + skiptop * t->co, -1, (t->li - skiptop) * t->co);
	msetI(t->attr + skiptop * t->co, BG_COLOR(bg_text), (t->li - skiptop) * t->co);
	msetI(t->sary, 0, t->li);
	msetI(t->updtab + skiptop, -1, t->li - skiptop);
	t->x = -1;
	t->y = -1;
	t->top = t->li;
	t->bot = 0;
	t->attrib = -1;
	t->ins = -1;
	set_attr(t, BG_COLOR(bg_text));
	clrins(t);
	setregn(t, 0, t->li);

	if (!skiptop) {
		if (t->cl) {
			texec(t->cap, t->cl, 1, 0, 0, 0, 0);
			t->x = 0;
			t->y = 0;
			msetI(t->scrn, ' ', t->li * t->co);
			msetI(t->attr, BG_COLOR(bg_text), t->li * t->co);
		} else if (t->cd) {
			cpos(t, 0, 0);
			texec(t->cap, t->cd, 1, 0, 0, 0, 0);
			msetI(t->scrn, ' ', t->li * t->co);
			msetI(t->attr, BG_COLOR(bg_text), t->li * t->co);
		}
	}
}
