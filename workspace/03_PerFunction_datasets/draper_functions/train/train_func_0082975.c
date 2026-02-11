ptab_init(int middle_c)
{
	int p;
	double pitch;
	free(__pitchtab);
	__pitchtab = malloc(129 * sizeof(int));
	if(!__pitchtab)
		return -1;

	pitch = (double)middle_c / FIVE_OCTAVES;
	for(p = 0; p < 129; ++p)
	{
		__pitchtab[p] = (int)pitch;
		pitch *= SEMITONE_MULTIPLIER;
	}
	return 0;
}
