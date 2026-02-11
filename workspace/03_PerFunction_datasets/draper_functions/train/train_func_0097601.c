do_filter(int *x, int *y, int n)
{
    int i, j;

    for (i = 0, j = 1; j < n; j++) {
	if (x[j] == x[i] && y[j] == y[i])
	    continue;
	i++;
	if (i == j)
	    continue;
	x[i] = x[j];
	y[i] = y[j];
    }

    return i + 1;
}
