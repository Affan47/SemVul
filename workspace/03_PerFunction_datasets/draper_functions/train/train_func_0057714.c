SpelParse(bname)
const char	*bname;
{
	Buffer	*buftospel,
		*wordsb;
	char	wordspel[100];
	Bufpos	*bp;
	struct error	*ep = NULL;

	ErrFree();

	buftospel = curbuf;
	wordsb = buf_exists(bname);
	if (wordsb == NULL)
		complain("Buffer %s is gone!", bname);
	perr_buf = wordsb;

	SetBuf(wordsb);
	ToFirst();
	f_mess("Finding misspelled words ... ");
	while (!lastp(curline)) {
		swritef(wordspel, sizeof(wordspel), "\\<%s\\>", linebuf);
		SetBuf(buftospel);
		ToFirst();
		while ((bp = dosearch(wordspel, FORWARD, NO)) != NULL) {
			SetDot(bp);
			ep = AddError(ep, wordsb->b_dot, buftospel,
					  curline, curchar);
		}
		SetBuf(wordsb);
		line_move(FORWARD, 1, NO);
	}
	add_mess("Done.");


	SetBuf(curwind->w_bufp);

	ShowErr();
}
