pow1p (gnm_float x, gnm_float y)
{
	if (gnm_abs (x) > 0.5)
		return gnm_pow (1 + x, y);
	else
		return gnm_exp (y * gnm_log1p (x));
}
