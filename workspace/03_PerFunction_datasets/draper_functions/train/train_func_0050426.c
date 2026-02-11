icxPlaneInterp(
double *v,
int    fdi,
int    di,
double *out,
double *in
) {
	int e, f;

	for (f = 0; f < fdi; f++) {
		for (out[f] = 0.0, e = 0; e < di; e++, v++) {
			out[f] += in[e] * *v;
		}
		out[f] += *v;
	}
}
