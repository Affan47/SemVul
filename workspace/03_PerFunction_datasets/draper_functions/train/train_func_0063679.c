pix_average(float *dp[], int n, float sigmas, int iter)
{
	int i;
	float m=0.0;
	for (i=0; i<n; i++) {
		m += *dp[i];
	}
	return m / n;
}
