icmLuv2XYZ(icmXYZNumber *w, double *out, double *in) {
	double un, vn, u, v, fl, fu, fv, sum, X, Y, Z;

	fl = (in[0] + 16.0)/116.0;
	fu = in[1] / (13.0 * in[0]);
	fv = in[2] / (13.0 * in[0]);

	un = (4.0 * w->X) / (w->X + 15.0 * w->Y + 3.0 * w->Z);
	vn = (9.0 * w->Y) / (w->X + 15.0 * w->Y + 3.0 * w->Z);

	u = fu + un;
	v = fv + vn;

	if (fl > 24.0/116.0)
		Y = pow(fl,3.0);
	else
		Y = (fl - 16.0/116.0)/7.787036979;
	Y *= w->Y;

	sum = (9.0 * Y)/v;
	X = (u * sum)/4.0;
	Z = (sum - X - 15.0 * Y)/3.0;

	out[0] = X;
	out[1] = Y;
	out[2] = Z;
}
