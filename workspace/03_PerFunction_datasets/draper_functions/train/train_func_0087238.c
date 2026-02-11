lfbaccdif (gnm_float a, gnm_float b)
{
	if (a > 0.03 * (a + b))
		return logfbit (a + b) - logfbit (b);
	else {
		gnm_float a2 = a * a;
		gnm_float ab2 = a / 2 + b;
		return a * (logfbit1 (ab2) + a2 / 24 *
			    (logfbit3 (ab2) + a2 / 80 *
			     (logfbit5 (ab2) + a2 / 168 *
			      logfbit7 (ab2))));
	}
}
