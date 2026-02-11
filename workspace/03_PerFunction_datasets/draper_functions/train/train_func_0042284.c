random_rayleigh (gnm_float sigma)
{
	gnm_float u;

	do {
		u = random_01 ();
	} while (u == 0.0);

	return sigma * gnm_sqrt (-2.0 * gnm_log (u));
}
