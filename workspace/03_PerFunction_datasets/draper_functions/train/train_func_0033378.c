gnumeric_binomdist (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float n = gnm_fake_floor (value_get_as_float (argv[0]));
	gnm_float trials = gnm_fake_floor (value_get_as_float (argv[1]));
	gnm_float p = value_get_as_float (argv[2]);
	gboolean cuml = value_get_as_checked_bool (argv[3]);

	if (n < 0 || trials < 0 || p < 0 || p > 1 || n > trials)
		return value_new_error_NUM (ei->pos);

	if (cuml)
		return value_new_float (pbinom (n, trials, p, TRUE, FALSE));
	else
		return value_new_float (dbinom (n, trials, p, FALSE));
}
