pfnext(BW *bw)
{
	if (!globalsrch) {
		return pffirst(bw);
	} else {
		SRCH *srch = globalsrch;

		globalsrch = 0;
		srch->addr = bw->cursor->byte;
		if (!srch->wrap_p || srch->wrap_p->b!=bw->b) {
			prm(srch->wrap_p);
			srch->wrap_p = pdup(bw->cursor, USTR "pfnext");
			srch->wrap_p->owner = &srch->wrap_p;
			srch->wrap_flag = 0;
		}
		return dopfnext(bw, setmark(srch), NULL);
	}
}
