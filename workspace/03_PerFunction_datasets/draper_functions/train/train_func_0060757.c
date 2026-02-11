select_minimum(__isl_take isl_basic_set *bset,
	__isl_keep isl_mat *var, int i)
{
	isl_ctx *ctx;
	int j, k;

	ctx = isl_mat_get_ctx(var);

	for (j = 0; j < var->n_row; ++j) {
		if (j == i)
			continue;
		k = isl_basic_set_alloc_inequality(bset);
		if (k < 0)
			goto error;
		isl_seq_combine(bset->ineq[k], ctx->one, var->row[j],
				ctx->negone, var->row[i], var->n_col);
		isl_int_set_si(bset->ineq[k][var->n_col], 0);
		if (j < i)
			isl_int_sub_ui(bset->ineq[k][0], bset->ineq[k][0], 1);
	}

	bset = isl_basic_set_finalize(bset);

	return bset;
error:
	isl_basic_set_free(bset);
	return NULL;
}
