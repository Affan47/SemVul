xdevlin_lin(
struct _xdevlin *p,
double *out,
double *in
) {
	co tc;
	int e;
	for (e = 0; e < p->di; e++) {
		tc.p[0] = in[e];
		p->curves[e]->interp(p->curves[e], &tc);
		out[e] = tc.v[0];
	}
}
