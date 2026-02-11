icxdpdiPlaneInterp(
double *v,
double *dv,
double *din,
int    fdi,
int    di,
double *out,
double *in
) {
	int e, ee, f, g;
	int dip2 = (di + 1);


	for (f = 0; f < fdi; f++) {
		for (out[f] = 0.0, e = 0; e < di; e++)
			out[f] += in[e] * v[f * dip2 + e];
		out[f] += v[f * dip2 + e];
	}


	for (e = 0; e < di; e++)
		dv[e] = in[e];
	dv[e] = 1.0;


	for (f = 0; f < fdi; f++) {
		for (e = 0; e < di; e++) {
			din[f * di + e] = v[f * dip2 + e];
		}
	}
}
