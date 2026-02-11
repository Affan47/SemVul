spline_averaging (const gnm_float *absc, const gnm_float *ord, int nb_knots,
		  const gnm_float *targets, int nb_targets)
{
	gnm_float *res;
	int i, imax;
	GnmCSpline *sp;
	if (!gnm_range_increasing (targets, nb_targets + 1))
		return NULL;
	sp = gnm_cspline_init (absc, ord, nb_knots,
			       GO_CSPLINE_NATURAL, 0., 0.);
	if (!sp)
		return NULL;
	res = gnm_cspline_get_integrals (sp, targets, nb_targets + 1);
	imax = nb_targets;
	for (i = 0; i < imax; i++)
		res[i] /= targets[i + 1] - targets[i];
	gnm_cspline_destroy (sp);
	return res;
}
