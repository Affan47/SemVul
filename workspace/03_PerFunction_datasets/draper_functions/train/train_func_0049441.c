gnumeric_fact (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float x = value_get_as_float (argv[0]);
	gboolean x_is_integer = (x == gnm_floor (x));

	if (x < 0 && x_is_integer)
		return value_new_error_NUM (ei->pos);

	return value_new_float (gnm_fact (x));
}
