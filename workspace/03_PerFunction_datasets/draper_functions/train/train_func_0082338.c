isl_seq_dump(isl_int *p, unsigned len)
{
	int i;

	for (i = 0; i < len; ++i) {
		if (i)
			fprintf(stderr, " ");
		isl_int_print(stderr, p[i], 0);
	}
	fprintf(stderr, "\n");
}
