udelbl(BW *bw)
{
	P *p = p_goto_bol(pdup(bw->cursor, USTR "udelbl"));

	if (p->byte == bw->cursor->byte) {
		prm(p);
		return ubacks(bw, 8);
	} else
		bdel(p, bw->cursor);
	prm(p);
	return 0;
}
