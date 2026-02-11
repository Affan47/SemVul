opt_bjer_stens (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	OptionSide call_put = option_side (value_peek_string (argv[0]));
	gnm_float s = value_get_as_float (argv[1]);
	gnm_float x = value_get_as_float (argv[2]);
	gnm_float t = value_get_as_float (argv[3]);
	gnm_float r = value_get_as_float (argv[4]);
	gnm_float v = value_get_as_float (argv[5]);
	gnm_float b = argv[6] ? value_get_as_float (argv[6]):0;
	gnm_float gfresult =
		opt_bjer_stens1 (call_put, s, x, t, r, v, b);
	return value_new_float (gfresult);
}
