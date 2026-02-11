e_cal_backend_sexp_func_time_add_day (ESExp *esexp,
                                      gint argc,
                                      ESExpResult **argv,
                                      gpointer data)
{
	ESExpResult *result;
	time_t t;
	gint n;

	g_return_val_if_fail (esexp != NULL, NULL);

	if (argc != 2) {
		e_sexp_fatal_error (
			esexp, _("\"%s\" expects two arguments"),
			"time-add-day");
		return NULL;
	}

	if (argv[0]->type != ESEXP_RES_TIME) {
		e_sexp_fatal_error (
			esexp, _("\"%s\" expects the first "
			"argument to be a time_t"),
			"time-add-day");
		return NULL;
	}
	t = argv[0]->value.time;

	if (argv[1]->type != ESEXP_RES_INT) {
		e_sexp_fatal_error (
			esexp, _("\"%s\" expects the second "
			"argument to be an integer"),
			"time-add-day");
		return NULL;
	}
	n = argv[1]->value.number;

	result = e_sexp_result_new (esexp, ESEXP_RES_TIME);
	result->value.time = time_add_day (t, n);

	return result;
}
