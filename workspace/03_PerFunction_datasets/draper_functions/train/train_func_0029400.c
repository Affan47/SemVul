gamma_large (gnm_float a)
{


	gnm_float sqa, x, y, v;
	sqa = gnm_sqrt (2 * a - 1);
	do {
		do {
			y = gnm_tan (M_PIgnum * random_01 ());
			x = sqa * y + a - 1;
		} while (x <= 0);
		v = random_01 ();
	} while (v > (1 + y * y) * gnm_exp ((a - 1) * gnm_log (x / (a - 1)) -
					    sqa * y));

	return x;
}
