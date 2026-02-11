gnumeric_dollarfr (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float x = value_get_as_float (argv[0]);
	gnm_float f = gnm_floor (value_get_as_float (argv[1]));
	gnm_float negative = FALSE;
	gnm_float fdigits;
	gnm_float res;

	if (f < 0)
		return value_new_error_NUM (ei->pos);
	if (f == 0)
		return value_new_error_DIV0 (ei->pos);

	if (x < 0) {
		negative = TRUE;
		x = gnm_abs (x);
	}


	fdigits = 1 + gnm_floor (gnm_log10 (f - 0.5));

	res = gnm_floor (x);
	res += (x - res) * f / gnm_pow10 (fdigits);

	if (negative)
		res = 0 - res;

	return value_new_float (res);
}
