init_scs_vert(void)
{
	int i;

	mpl = 1;
	tm = 1;
	bm = mpl;
	vtabs[1] = 1;
	for (i = 0; i <= MAX_MPL; i++) {
		vtabs[i] = 0;
	}
}
