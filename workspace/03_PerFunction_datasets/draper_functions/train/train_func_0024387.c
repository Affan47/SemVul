doinsf(BW *bw, unsigned char *s, void *object, int *notify)
{
	if (notify)
		*notify = 1;
	if (square)
		if (markv(2)) {
			B *tmp;
			long width = markk->xcol - markb->xcol;
			long height;
			int usetabs = ptabrect(markb,
					       markk->line - markb->line + 1,
					       markk->xcol);

			tmp = bload(s);
			if (berror) {
				msgnw(bw->parent, joe_gettext(msgs[-berror]));
				brm(tmp);
				return -1;
			}
			if (piscol(tmp->eof))
				height = tmp->eof->line + 1;
			else
				height = tmp->eof->line;
			if (bw->o.overtype) {
				pclrrect(markb, long_max(markk->line - markb->line + 1, height), markk->xcol, usetabs);
				pdelrect(markb, height, width + markb->xcol);
			}
			pinsrect(markb, tmp, width, usetabs);
			pdupown(markb, &markk, USTR "doinsf");
			markk->xcol = markb->xcol;
			if (height) {
				pline(markk, markk->line + height - 1);
				pcol(markk, markb->xcol + width);
				markk->xcol = markb->xcol + width;
			}
			brm(tmp);
			updall();
			return 0;
		} else {
			msgnw(bw->parent, joe_gettext(_("No block")));
			return -1;
	} else {
		int ret = 0;
		B *tmp = bload(s);

		if (berror) {
			msgnw(bw->parent, joe_gettext(msgs[-berror])), brm(tmp);
			ret = -1;
		} else
			binsb(bw->cursor, tmp);
		vsrm(s);
		bw->cursor->xcol = piscol(bw->cursor);
		return ret;
	}
}
