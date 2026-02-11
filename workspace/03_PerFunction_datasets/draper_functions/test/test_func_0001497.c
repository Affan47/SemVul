GMT_d_read (FILE *fp, double *d)
{
	if (!GMT_fread ((void *)d, sizeof (double), (size_t)1, fp)) return (0);
	if (GMT_do_swab) {
		unsigned int *i, j;
		i = (unsigned int *)d;
		j = GMT_swab4 (i[0]);
		i[0] = GMT_swab4 (i[1]);
		i[1] = j;
	}
	return (1);
}
