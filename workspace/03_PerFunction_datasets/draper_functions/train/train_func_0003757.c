count_distinct_values (const double *x, int n)
{
    int i, c = 1;

    for (i=1; i<n; i++) {
	if (x[i] != x[i-1]) {
	    c++;
	}
    }

    return c;
}
