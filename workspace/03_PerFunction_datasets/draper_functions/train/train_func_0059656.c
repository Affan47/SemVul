gnumeric_percentile (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float *data;
	GnmValue *result = NULL;
	int n;

	data = collect_floats_value (argv[0], ei->pos,
				     COLLECT_IGNORE_STRINGS |
				     COLLECT_IGNORE_BOOLS |
				     COLLECT_IGNORE_BLANKS |
				     COLLECT_SORT,
				     &n, &result);
	if (!result) {
		gnm_float p = value_get_as_float (argv[1]);
		gnm_float res;

		if (gnm_range_fractile_inter_sorted (data, n, &res, p))
			result = value_new_error_NUM (ei->pos);
		else
			result = value_new_float (res);
	}

	g_free (data);
	return result;
}
