SetLMargin()
{
	int	lmarg = calc_pos(linebuf, curchar);

	if (lmarg >= RMargin)
		complain("[Left margin must be left of right margin]");
	LMargin = lmarg;
}
