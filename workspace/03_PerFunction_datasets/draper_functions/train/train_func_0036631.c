icmMul3x3(double dst[3][3], double src[3][3]) {
	int i, j, k;
	double td[3][3];

	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			double tt = 0.0;
			for (k = 0; k < 3; k++)
				tt += src[j][k] * dst[k][i];
			td[j][i] = tt;
		}
	}


	for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
			dst[j][i] = td[j][i];
}
