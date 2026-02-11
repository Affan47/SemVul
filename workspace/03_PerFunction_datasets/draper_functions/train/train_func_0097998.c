gsl_complex_tanh (complex_t const *a, complex_t *res)
{
        gnm_float R = GSL_REAL (a), I = GSL_IMAG (a);

	if (gnm_abs (R) < 1.0) {
	         gnm_float D =
			 gnm_pow (gnm_cos (I), 2.0) +
			 gnm_pow (gnm_sinh (R), 2.0);

		 complex_init (res, gnm_sinh (R) * cosh (R) / D,
			       0.5 * gnm_sin (2 * I) / D);
	} else {
	         gnm_float D =
			 gnm_pow (gnm_cos (I), 2.0) +
			 gnm_pow (gnm_sinh (R), 2.0);
		 gnm_float F = 1 + gnm_pow (gnm_cos (I) / gnm_sinh (R), 2.0);

		 complex_init (res, 1.0 / (gnm_tanh (R) * F),
			       0.5 * gnm_sin (2 * I) / D);
	}
}
