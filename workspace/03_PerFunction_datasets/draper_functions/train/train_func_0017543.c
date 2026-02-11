random_logistic (gnm_float a)
{
	gnm_float x;

	do {
		x = random_01 ();
	} while (x == 0 || x == 1);

	return a * gnm_log (x / (1 - x));
}
