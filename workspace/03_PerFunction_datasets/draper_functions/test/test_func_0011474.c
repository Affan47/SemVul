gnumeric_cronbach (GnmFuncEvalInfo *ei, int argc, GnmExprConstPtr const *argv)
{
	int         i, j;
	GnmValue **values;
	gnm_float sum_variance = 0.0;
	gnm_float sum_covariance = 0.0;

	if (argc < 2)
		return value_new_error_VALUE (ei->pos);

	for (i = 0; i < argc; i++) {
		GnmValue *fl_val =
			float_range_function (1, argv + i, ei,
					      gnm_range_var_pop, 0,
					      GNM_ERROR_VALUE);
		if (!VALUE_IS_NUMBER (fl_val))
			return fl_val;
		sum_variance += value_get_as_float (fl_val);
		value_release (fl_val);
	}

	values = g_new0 (GnmValue *, argc);

	for (i = 0; i < argc; i++) {
		GnmValue *type_mismatch;

		values[i] = function_marshal_arg (ei, argv[i], &type_mismatch);
		if (type_mismatch || values[i] == NULL) {
			free_values (values, i + 1);
			if (type_mismatch)
				return type_mismatch;
			else
				return value_new_error_VALUE (ei->pos);
		}
	}

	g_return_val_if_fail (i == argc, value_new_error_VALUE (ei->pos));


	for (i = 0; i < argc; ++i) {
		for (j = i + 1; j < argc; ++j) {
			GnmValue *fl_val;
			fl_val = float_range_function2 (values[i], values[j],
							ei,
							gnm_range_covar_pop, 0,
							GNM_ERROR_VALUE);
			if (!VALUE_IS_NUMBER (fl_val)) {
				free_values (values, argc);
				return fl_val;
			}
			sum_covariance += value_get_as_float (fl_val);
			value_release (fl_val);
		}
	}

	free_values (values, argc);
	return  value_new_float
		(argc * (1 - sum_variance / (sum_variance + 2 * sum_covariance)) / (argc - 1));
}
