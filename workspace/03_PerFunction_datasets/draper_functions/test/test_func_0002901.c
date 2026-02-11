l2y_curve(double *out, double *in, int isXYZ) {
	int i;
	double val;
	double isc = 1.0, osc = 1.0;


	if (isXYZ) {
		isc = 32768.0/65535.0;
		osc = 65535.0/32768.0 / YSCALE;
	}


	for (i = 0; i < 3; i++) {
		val = in[i] * isc;
		if (val > 0.08)
			val = pow((val + 0.16)/1.16, 3.0);
		else
			val = val/9.032962896;
		out[i] = val * osc;
	}
}
