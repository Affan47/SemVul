banwd(const char *word)
{
	int  row, cnt;
	const	char  *cp;
	int	Pwidth = in_params.pi_width > 10? in_params.pi_width: 80;

	for  (row = 0;  row < 16;  row++)  {
		for  (cp = word, cnt = 8;  *cp && cnt < Pwidth;  cp++, cnt += 8)
			banch(*cp, row);
		lcnt++;
		(*pfunc)('\n');
	}
}
