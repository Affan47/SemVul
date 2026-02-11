nxti(void)
{
	int i, max, maxi;

	max = 0;
	maxi = 0;
	for(i = 1; i <= nnonter; i++)
		if(ggreed[i] >= max) {
			max = ggreed[i];
			maxi = -i;
		}
	for(i = 0; i < nstate; ++i)
		if(tystate[i] >= max) {
			max = tystate[i];
			maxi = i;
		}
	if(nxdb)
		Bprint(ftable, "nxti = %d, max = %d\n", maxi, max);
	if(max == 0)
		return NOMORE;
	return maxi;
}
