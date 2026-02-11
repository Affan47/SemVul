pair_freq_iter(int n, double *pdg[2], double f[4])
{
	double ff[4];
	int i, k, h;

	memset(ff, 0, 4 * sizeof(double));
	for (i = 0; i < n; ++i) {
		double *p[2], sum, tmp;
		p[0] = pdg[0] + i * 3; p[1] = pdg[1] + i * 3;
		for (k = 0, sum = 0.; k < 4; ++k)
			for (h = 0; h < 4; ++h)
				sum += f[k] * f[h] * p[0][_G1(k,h)] * p[1][_G2(k,h)];
		for (k = 0; k < 4; ++k) {
			tmp = f[0] * (p[0][_G1(0,k)] * p[1][_G2(0,k)] + p[0][_G1(k,0)] * p[1][_G2(k,0)])
				+ f[1] * (p[0][_G1(1,k)] * p[1][_G2(1,k)] + p[0][_G1(k,1)] * p[1][_G2(k,1)])
				+ f[2] * (p[0][_G1(2,k)] * p[1][_G2(2,k)] + p[0][_G1(k,2)] * p[1][_G2(k,2)])
				+ f[3] * (p[0][_G1(3,k)] * p[1][_G2(3,k)] + p[0][_G1(k,3)] * p[1][_G2(k,3)]);
			ff[k] += f[k] * tmp / sum;
		}
	}
	for (k = 0; k < 4; ++k) f[k] = ff[k] / (2 * n);
	return 0;
}
