collect_inequalities(__isl_take isl_mat *mat,
	__isl_keep isl_basic_set_list *list, isl_int **ineq)
{
	int i, j, n, n_eq, n_ineq;

	if (!mat)
		return NULL;

	n_eq = 0;
	n_ineq = 0;
	n = isl_basic_set_list_n_basic_set(list);
	for (i = 0; i < n; ++i) {
		isl_basic_set *bset;
		bset = isl_basic_set_list_get_basic_set(list, i);
		if (!bset)
			return isl_mat_free(mat);
		for (j = 0; j < bset->n_eq; ++j) {
			ineq[n_ineq++] = mat->row[n_eq];
			ineq[n_ineq++] = bset->eq[j];
			isl_seq_neg(mat->row[n_eq++], bset->eq[j], mat->n_col);
		}
		for (j = 0; j < bset->n_ineq; ++j)
			ineq[n_ineq++] = bset->ineq[j];
		isl_basic_set_free(bset);
	}

	return mat;
}
