transfer_s_p_options(s_p_options_t **full_options,
				 s_p_options_t *options,
				 int *full_options_cnt)
{
	s_p_options_t *op = NULL;
	s_p_options_t *full_options_ptr;
	int cnt = *full_options_cnt;

	xassert(full_options);

	for (op = options; op->key != NULL; op++, cnt++) {
		xrealloc(*full_options, ((cnt + 1) * sizeof(s_p_options_t)));
		full_options_ptr = &(*full_options)[cnt];
		full_options_ptr->key = xstrdup(op->key);
		full_options_ptr->type = op->type;
	}
	*full_options_cnt = cnt;
}
