buflist_getfile(n, lnum, setpm)
	int			n;
	linenr_t	lnum;
	int			setpm;
{
	BUF		*buf;

	buf = buflist_findnr(n);
	if (buf == NULL)
	{
		emsg(e_noalt);
		return FAIL;
	}
	if (lnum == 0)
		lnum = buflist_findlnum(buf);
	RedrawingDisabled = TRUE;
	if (getfile(buf->b_filename, buf->b_sfilename, setpm, lnum) <= 0)
	{
		RedrawingDisabled = FALSE;
		return OK;
	}
	RedrawingDisabled = FALSE;
	return FAIL;
}
