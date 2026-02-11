gsl_complex_arcsin_real (gnm_float a, complex_t *res)
{
         if (gnm_abs (a) <= 1.0) {
	         complex_init (res, gnm_asin (a), 0.0);
	 } else {
	         if (a < 0.0) {
		         complex_init (res, -M_PI_2gnum, gnm_acosh (-a));
		 } else {
		         complex_init (res, M_PI_2gnum, -gnm_acosh (a));
		 }
	 }
}
