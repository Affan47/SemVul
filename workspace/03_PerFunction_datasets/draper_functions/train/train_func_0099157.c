I_alloc_double3(int a, int b, int c)
{
    double ***x;
    int i, n;

    x = (double ***)G_malloc((a + 1) * sizeof(double **));

    for (i = 0; i < a; i++) {
	x[i] = I_alloc_double2(b, c);
	if (x[i] == NULL) {
	    for (n = 0; n < i; n++)
		G_free(x[n]);
	    G_free(x);

	    return (double ***)NULL;
	}
    }
    x[a] = NULL;

    return x;
}
