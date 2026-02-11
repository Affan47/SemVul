gnumeric_decimal (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float base = value_get_as_float (argv[1]);

	if (base < 2 || base >= 37)
		return value_new_error_NUM (ei->pos);

	return value_new_error_NUM (ei->pos);
}
