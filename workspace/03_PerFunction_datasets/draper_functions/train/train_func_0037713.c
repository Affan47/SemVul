gnumeric_gammadist (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float x = value_get_as_float (argv[0]);
	gnm_float alpha = value_get_as_float (argv[1]);
	gnm_float beta = value_get_as_float (argv[2]);
	gboolean cum = value_get_as_checked_bool (argv[3]);

	if (x < 0 || alpha <= 0 || beta <= 0)
		return value_new_error_NUM (ei->pos);

	if (cum)
		return value_new_float (pgamma (x, alpha, beta, TRUE, FALSE));
	else
		return value_new_float (dgamma (x, alpha, beta, FALSE));
}
