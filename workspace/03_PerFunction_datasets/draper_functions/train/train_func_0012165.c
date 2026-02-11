sol_pop(struct isl_sol *sol)
{
	struct isl_partial_sol *partial;
	unsigned n_div;

	if (sol->error)
		return;

	if (sol->level == 0) {
		for (partial = sol->partial; partial; partial = sol->partial)
			sol_pop_one(sol);
		return;
	}

	partial = sol->partial;
	if (!partial)
		return;

	if (partial->level <= sol->level)
		return;

	if (partial->next && partial->next->level == partial->level) {
		n_div = isl_basic_set_dim(
				sol->context->op->peek_basic_set(sol->context),
				isl_dim_div);

		if (!same_solution(partial, partial->next, n_div)) {
			sol_pop_one(sol);
			sol_pop_one(sol);
		} else {
			struct isl_basic_set *bset;
			isl_mat *M;
			unsigned n;

			n = isl_basic_set_dim(partial->next->dom, isl_dim_div);
			n -= n_div;
			bset = sol_domain(sol);
			isl_basic_set_free(partial->next->dom);
			partial->next->dom = bset;
			M = partial->next->M;
			if (M) {
				M = isl_mat_drop_cols(M, M->n_col - n, n);
				partial->next->M = M;
				if (!M)
					goto error;
			}
			partial->next->level = sol->level;

			if (!bset)
				goto error;

			sol->partial = partial->next;
			isl_basic_set_free(partial->dom);
			isl_mat_free(partial->M);
			free(partial);
		}
	} else
		sol_pop_one(sol);

	if (0)
error:		sol->error = 1;
}
