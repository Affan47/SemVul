gnumeric_pfactor (GnmFuncEvalInfo *ei, GnmValue const * const *args)
{
	gnm_float n = gnm_floor (value_get_as_float (args[0]));
	gint64 p;

	if (n < 2)
		return value_new_error_VALUE (ei->pos);
	if (n > bit_max)
		p = 0;
	else
		p = prime_factor ((guint64)n);

	if (p == 0)
		return value_new_error (ei->pos, OUT_OF_BOUNDS);

	return value_new_float (p);
}
