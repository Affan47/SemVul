icmVecRotMat(double m[3][4], double s1[3], double s0[3], double t1[3], double t0[3]) {
	int i, j;
	double ss[3], tt[3], rr[3][3];


	for (i = 0; i < 3; i++) {
		ss[i] = s1[i] - s0[i];
		tt[i] = t1[i] - t0[i];
	}
	icmRotMat(rr, ss, tt);


	icmMulBy3x3(ss, rr, s0);


	for (j = 0; j < 3; j++) {
		for (i = 0; i < 4; i++) {
			if (i < 3 && j < 3)
				m[j][i] = rr[j][i];
			else if (i == 3 && j < 3)
				m[j][i] = t0[j] - ss[j];
			else if (i == j)
				m[j][i] = 1.0;
			else
				m[j][i] = 0.0;
		}
	}
}
