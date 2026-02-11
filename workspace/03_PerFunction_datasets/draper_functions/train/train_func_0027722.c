readcodelist(const int obey, ULONG *result, const unsigned lo, const unsigned hi)
{
	int	ch;
	unsigned  nn, nn2;
	if  (obey)  {
		nn = lo >> 5;
		nn2 = hi >> 5;
		while  (nn <= nn2)
			result[nn++] = 0;
	}
	for  (;;)  {
		nn = (unsigned) rdnum();
		if  (nn < lo || nn > hi)  {
			disp_arg[1] = nn;
			disp_arg[2] = lo;
			disp_arg[3] = hi;
			error(1052);
		}
		do ch = getc(infile);
		while  (ch == ' ' || ch == '\t');
		if  (ch == '-')  {
			nn2 = (unsigned) rdnum();
			do ch = getc(infile);
			while  (ch == ' ' || ch == '\t');
		}
		else
			nn2 = nn;
		if  (obey)  {
			if  (nn2 < nn)  {
				unsigned  tmp = nn;
				nn = nn2;
				nn2 = tmp;
			}
			while  (nn <= nn2)  {
				result[nn >> 5] |= 1 << (nn & 31);
				nn++;
			}
		}
		if  (ch == '\n')  {
			line_count++;
			return;
		}
		if  (ch != ',')
			error(1053);
	}
}
