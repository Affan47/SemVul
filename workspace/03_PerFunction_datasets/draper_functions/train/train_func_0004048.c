gnumeric_delta (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float x = value_get_as_float (argv[0]);
	gnm_float y = argv[1] ? value_get_as_float (argv[1]) : 0;

	return value_new_int (x == y);
}
