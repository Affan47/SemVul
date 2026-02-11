doline(BW *bw, unsigned char *s, void *object, int *notify)
{
	long num = calc(bw, s);

	if (notify)
		*notify = 1;
	vsrm(s);
	if (num >= 1 && !merr) {
		int tmp = mid;

		if (num > bw->b->eof->line)
			num = bw->b->eof->line + 1;
		pline(bw->cursor, num - 1), bw->cursor->xcol = piscol(bw->cursor);
		mid = 1;
		dofollows();
		mid = tmp;
		return 0;
	} else {
		if (merr)
			msgnw(bw->parent, merr);
		else
			msgnw(bw->parent, joe_gettext(_("Invalid line number")));
		return -1;
	}
}
