nclose(SCRN *t)
{
	leave = 1;
	set_attr(t, 0);
	clrins(t);
	setregn(t, 0, t->li);
	cpos(t, 0, t->li - 1);
	if (t->te)
		texec(t->cap, t->te, 1, 0, 0, 0, 0);
	ttclose();
	rmcap(t->cap);
	joe_free(t->scrn);
	joe_free(t->attr);
	joe_free(t->sary);
	joe_free(t->ofst);
	joe_free(t->htab);
	joe_free(t->ary);
	joe_free(t);
}
