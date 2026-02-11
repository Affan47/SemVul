gsl_complex_arcsin (complex_t const *a, complex_t *res)
{
        gnm_float R = GSL_REAL (a), I = GSL_IMAG (a);

	if (I == 0) {
	        gsl_complex_arcsin_real (R, res);
	} else {
	        gnm_float x = gnm_abs (R), y = gnm_abs (I);
		gnm_float r = gnm_hypot (x + 1, y);
		gnm_float s = gnm_hypot (x - 1, y);
		gnm_float A = 0.5 * (r + s);
		gnm_float B = x / A;
		gnm_float y2 = y * y;

		gnm_float real, imag;

		const gnm_float A_crossover = 1.5, B_crossover = 0.6417;

		if (B <= B_crossover) {
		        real = gnm_asin (B);
		} else {
		        if (x <= 1) {
			        gnm_float D = 0.5 * (A + x) *
				        (y2 / (r + x + 1) + (s + (1 - x)));
				real = gnm_atan (x / gnm_sqrt (D));
			} else {
			        gnm_float Apx = A + x;
				gnm_float D = 0.5 * (Apx / (r + x + 1)
						      + Apx / (s + (x - 1)));
				real = gnm_atan (x / (y * gnm_sqrt (D)));
			}
		}

		if (A <= A_crossover) {
		        gnm_float Am1;

			if (x < 1) {
			        Am1 = 0.5 * (y2 / (r + (x + 1)) + y2 /
					     (s + (1 - x)));
			} else {
			        Am1 = 0.5 * (y2 / (r + (x + 1)) +
					     (s + (x - 1)));
			}

			imag = gnm_log1p (Am1 + gnm_sqrt (Am1 * (A + 1)));
		} else {
		        imag = gnm_log (A + gnm_sqrt (A * A - 1));
		}

		complex_init (res, (R >= 0) ? real : -real, (I >= 0) ?
			      imag : -imag);
	}
}
