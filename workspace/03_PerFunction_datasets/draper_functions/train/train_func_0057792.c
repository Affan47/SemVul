constant_phi_v(const gsl_vector *x, void *params, gsl_vector *f)
{
	double kappa, kphi, phi;
	size_t i;
	HklPseudoAxisEngine *engine = params;
	double p0 = engine->mode->parameters[0].value;
	double const *x_data = x->data;
	double *f_data = f->data;

	for(i=0; i<x->size;++i)
		if (gsl_isnan(x_data[i]))
			return GSL_ENOMEM;

	RUBh_minus_Q(x_data, params, f_data);

	kappa = x_data[1];
	kphi = x_data[2];

	phi = kphi + atan(tan(kappa/2.)*cos(50 * HKL_DEGTORAD)) + M_PI_2;

	f_data[3] = p0 - phi;

	return  GSL_SUCCESS;
}
