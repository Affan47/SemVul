isl_basic_set_is_box(__isl_keep isl_basic_set *bset)
{
	int i, j;
	unsigned nvar;
	unsigned ovar;

	if (!bset)
		return -1;

	if (isl_basic_set_dim(bset, isl_dim_div) != 0)
		return 0;

	nvar = isl_basic_set_dim(bset, isl_dim_set);
	ovar = isl_space_offset(bset->dim, isl_dim_set);
	for (j = 0; j < nvar; ++j) {
		int lower = 0, upper = 0;
		for (i = 0; i < bset->n_eq; ++i) {
			if (isl_int_is_zero(bset->eq[i][1 + ovar + j]))
				continue;
			if (!unique(bset->eq[i] + 1 + ovar, j, nvar))
				return 0;
			break;
		}
		if (i < bset->n_eq)
			continue;
		for (i = 0; i < bset->n_ineq; ++i) {
			if (isl_int_is_zero(bset->ineq[i][1 + ovar + j]))
				continue;
			if (!unique(bset->ineq[i] + 1 + ovar, j, nvar))
				return 0;
			if (isl_int_is_pos(bset->ineq[i][1 + ovar + j]))
				lower = 1;
			else
				upper = 1;
		}
		if (!lower || !upper)
			return 0;
	}

	return 1;
}
