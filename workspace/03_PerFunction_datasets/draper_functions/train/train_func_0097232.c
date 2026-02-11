printtable(const short *table, int limit)
{
	int i;

	printf("# This is the distribution table for the experimental distribution.\n");

	for (i=0 ; i < limit; ++i) {
		printf("%d%c", table[i],
		       (i % 8) == 7 ? '\n' : ' ');
	}
}
