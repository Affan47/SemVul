spline3d_Wessel_Bercovici (double r, double par[], double *G)


{
	double cx;

	if (r == 0.0) return (0.0);

	cx = par[0] * r;
	return (((exp (-cx) - 1.0) / cx) + 1.0);
}
