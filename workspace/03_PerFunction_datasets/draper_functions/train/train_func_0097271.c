icmYxy2XYZ(double *out, double *in) {
	double Y = in[0];
	double x = in[1];
	double y = in[2];
	double z = 1.0 - x - y;
	double sum;
	if (y < 1e-9) {
		out[0] = out[1] = out[2] = 0.0;
	} else {
		sum = Y/y;
		out[0] = x * sum;
		out[1] = Y;
		out[2] = z * sum;
	}
}
