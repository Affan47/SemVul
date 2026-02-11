gnumeric_seriessum (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float x = value_get_as_float (argv[0]);
	gnm_float n = value_get_as_float (argv[1]);
	gnm_float m = value_get_as_float (argv[2]);
	GnmValue *result = NULL;
	int N;

	gnm_float *data =
		collect_floats_value (argv[3], ei->pos,
				      COLLECT_IGNORE_BLANKS, &N, &result);

	if (result)
		goto done;

	if (x == 0) {
		if (n <= 0 || n + (N - 1) * m <= 0)
			result = value_new_error_NUM (ei->pos);
		else
			result = value_new_float (0);
	} else {
		gnm_float x_m = gnm_pow (x, m);
		gnm_float sum = 0;
		int i;
		x = gnm_pow (x, n);

		for (i = 0; i < N; i++) {
			sum += data[i] * x;
			x *= x_m;
		}

		if (gnm_finite (sum))
			result = value_new_float (sum);
		else
			result = value_new_error_NUM (ei->pos);
	}

done:
	g_free (data);
	return result;
}
