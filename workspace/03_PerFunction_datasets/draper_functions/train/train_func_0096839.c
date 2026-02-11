isl_tab_set_initial_basis_with_cone(struct isl_tab *tab,
	struct isl_tab *tab_cone)
{
	struct isl_mat *eq;
	struct isl_mat *cone_eq;
	struct isl_mat *U, *Q;

	if (!tab || !tab_cone)
		return -1;

	if (tab_cone->n_col == tab_cone->n_dead) {
		tab->basis = initial_basis(tab);
		return tab->basis ? 0 : -1;
	}

	eq = tab_equalities(tab);
	if (!eq)
		return -1;
	tab->n_zero = eq->n_row;
	cone_eq = tab_equalities(tab_cone);
	eq = isl_mat_concat(eq, cone_eq);
	if (!eq)
		return -1;
	tab->n_unbounded = tab->n_var - (eq->n_row - tab->n_zero);
	eq = isl_mat_left_hermite(eq, 0, &U, &Q);
	if (!eq)
		return -1;
	isl_mat_free(eq);
	tab->basis = isl_mat_lin_to_aff(Q);
	if (tab_shift_cone(tab, tab_cone, U) < 0)
		return -1;
	if (!tab->basis)
		return -1;
	return 0;
}
