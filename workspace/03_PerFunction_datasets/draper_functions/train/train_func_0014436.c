e_cal_backend_sexp_func_time_now (ESExp *esexp,
                                  gint argc,
                                  ESExpResult **argv,
                                  gpointer data)
{
	ESExpResult *result;

	g_return_val_if_fail (esexp != NULL, NULL);

	if (argc != 0) {
		e_sexp_fatal_error (
			esexp, _("\"%s\" expects no arguments"),
			"time-now");
		return NULL;
	}

	result = e_sexp_result_new (esexp, ESEXP_RES_TIME);
	result->value.time = time (NULL);

	return result;
}
