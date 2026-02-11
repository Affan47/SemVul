daxpy_(int n, double da, double *dx, double *dy)
{
    int i, m;

    if (n <= 0 || da == 0) {
	return;
    }

    m = n % 4;

    if (m != 0) {
	for (i = 0; i < m; ++i) {
	    dy[i] += da * dx[i];
	}
	if (n < 4) {
	    return;
	}
    }

    for (i = m; i < n; i += 4) {
	dy[i] += da * dx[i];
	dy[i + 1] += da * dx[i + 1];
	dy[i + 2] += da * dx[i + 2];
	dy[i + 3] += da * dx[i + 3];
    }
}
