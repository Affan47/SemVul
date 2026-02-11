gnumeric_ipmt (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float rate = value_get_as_float (argv[0]);
	gnm_float per  = value_get_as_float (argv[1]);
	gnm_float nper = value_get_as_float (argv[2]);
	gnm_float pv   = value_get_as_float (argv[3]);
	gnm_float fv   = argv[4] ? value_get_as_float (argv[4]) : 0;
	int type       = value_get_paytype (argv[5]);


	if (per < 1 || per >= nper + 1)
                return value_new_error_NUM (ei->pos);

	if (!is_valid_paytype (type))
		return value_new_error_VALUE (ei->pos);

	return value_new_float (calculate_ipmt (rate, per, nper, pv, fv, type));
}
