gnumeric_prob (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	GnmValue *res;
	GnmValue *error = NULL;
	int i, prob_n, x_n;
	gnm_float *prob_vals = NULL, *x_vals = NULL;
	gnm_float lower_limit, upper_limit;
	gnm_float total_sum = 0, sum = 0;

	lower_limit = value_get_as_float (argv[2]);
	upper_limit = argv[3] ? value_get_as_float (argv[3]) : lower_limit;

	x_vals = collect_floats_value
		(argv[0], ei->pos,
		 COLLECT_IGNORE_STRINGS | COLLECT_IGNORE_BOOLS |
		 COLLECT_IGNORE_BLANKS,
		 &x_n, &error);
	if (error) {
		res = error;
		goto out;
	}

	prob_vals = collect_floats_value
		(argv[1], ei->pos,
		 COLLECT_IGNORE_STRINGS | COLLECT_IGNORE_BOOLS |
		 COLLECT_IGNORE_BLANKS,
		 &prob_n, &error);
	if (error) {
		res = error;
		goto out;
	}

	if (x_n != prob_n) {
		res = value_new_error_NA (ei->pos);
		goto out;
	}

	for (i = 0; i < x_n; i++) {
		gnm_float x = x_vals[i];
		gnm_float prob = prob_vals[i];


		if (prob <= 0 || prob > 1) {
			res = value_new_error_NUM (ei->pos);
			goto out;
		}

		total_sum += prob;

		if (x >= lower_limit && x <= upper_limit)
			sum += prob;
	}

	if (gnm_abs (total_sum - 1) > x_n * 2 * GNM_EPSILON) {
		res = value_new_error_NUM (ei->pos);
		goto out;
	}

	res = value_new_float (sum);

 out:
	g_free (x_vals);
	g_free (prob_vals);
	return res;
}
