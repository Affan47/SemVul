n_mot(void)
{
	int j, n;
	Tchar i;

	j = HOR;
	getch();
	if (n = atoi0()) {
		if (vflag)
			j = VERT;
		i = makem(quant(n, j));
	} else
		i = 0;
	getch();
	vflag = 0;
	dfact = 1;
	return(i);
}
