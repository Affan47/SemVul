e_sexp_evaluate_occur_times (ESExp *f,
                             time_t *start,
                             time_t *end)
{
	struct _ESExpResult *r;
	gboolean generator;
	g_return_val_if_fail (IS_E_SEXP (f), FALSE);
	g_return_val_if_fail (f->tree != NULL, FALSE);
	g_return_val_if_fail (start != NULL, FALSE);
	g_return_val_if_fail (end != NULL, FALSE);

	*start = *end = -1;

	if (setjmp (f->failenv)) {
		g_warning ("Error in execution: %s", f->error);
		return FALSE;
	}

	r = e_sexp_term_evaluate_occur_times (f, f->tree, start, end);
	generator = r->time_generator;

	if (generator) {
		*start = r->occuring_start;
		*end = r->occuring_end;
	}

	e_sexp_result_free (f, r);

	return generator;
}
