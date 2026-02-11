gnumeric_g_duration (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float rate, pv, fv;

	rate = value_get_as_float (argv[0]);
	pv   = value_get_as_float (argv[1]);
	fv   = value_get_as_float (argv[2]);

	if (rate <= 0)
		return value_new_error_DIV0 (ei->pos);
	else if (fv == 0 || pv == 0)
		return value_new_error_DIV0 (ei->pos);
	else if (fv / pv < 0)
		return value_new_error_VALUE (ei->pos);

        return value_new_float (gnm_log (fv / pv) / gnm_log1p (rate));

}
