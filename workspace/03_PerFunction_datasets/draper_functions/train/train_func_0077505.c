add_to_used_opt_idx(con, opt_idx)
	const CFG_CONTEXT con;
	int               opt_idx;
{
	int *p_i = NULL;

	if (opt_idx < 0)
		return 1;

	if (con->used_opt_idx != NULL)
		for (p_i = con->used_opt_idx; *p_i >= 0; p_i++)
			if (*p_i == opt_idx)
				return 1;

	if (p_i == NULL || *p_i == -255) {
		register int *p_j;
		register int new_size;

		new_size = (p_i == NULL ? 0 : p_i - con->used_opt_idx)
			+ 1 + CFG_USED_OPT_IDX_STEP;

		con->used_opt_idx = (int *) realloc(con->used_opt_idx,
				new_size * sizeof(int));

#if defined(DEBUG) && DEBUG
		printf("add_to_used_opt_idx(con, %d): realloc(%d) = %p\n",
				opt_idx, new_size, (void *) con->used_opt_idx);
#endif

		if (con->used_opt_idx == NULL)
			return -1;

		if (p_i == NULL)
			p_i = con->used_opt_idx;
		else
			for (p_i = con->used_opt_idx; *p_i >= 0; p_i++) ;

		for (p_j = p_i; p_j - p_i < CFG_USED_OPT_IDX_STEP; p_j++)
			*p_j = -1;

		*p_j = -255;
	}

	*p_i = opt_idx;

	return 0;
}
