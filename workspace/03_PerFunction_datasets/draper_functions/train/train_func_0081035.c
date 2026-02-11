makedist(double *x, int limit, double mu, double sigma)
{
	int *table;
	int i, index, first=DISTTABLESIZE, last=0;
	double input;

	table = calloc(DISTTABLESIZE, sizeof(int));
	if (!table) {
		perror("table alloc");
		exit(3);
	}

	for (i=0; i < limit; ++i) {

		input = (x[i]-mu)/sigma;

		index = (int)rint((input+DISTTABLEDOMAIN)*DISTTABLEGRANULARITY);
		if (index < 0) index = 0;
		if (index >= DISTTABLESIZE) index = DISTTABLESIZE-1;
		++table[index];
		if (index > last)
			last = index +1;
		if (index < first)
			first = index;
	}
	return table;
}
