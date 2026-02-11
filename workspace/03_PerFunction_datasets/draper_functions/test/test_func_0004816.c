print_basic_set_c(__isl_take isl_printer *p,
	__isl_keep isl_space *dim, __isl_keep isl_basic_set *bset)
{
	int i, j;
	int first = 1;
	unsigned n_div = isl_basic_set_dim(bset, isl_dim_div);
	unsigned total = isl_basic_set_total_dim(bset) - n_div;

	for (i = 0; i < bset->n_eq; ++i) {
		j = isl_seq_last_non_zero(bset->eq[i] + 1 + total, n_div);
		if (j < 0)
			p = print_constraint_c(p, dim, bset,
						bset->eq[i], "==", &first);
		else {
			if (i)
				p = isl_printer_print_str(p, " && ");
			p = isl_printer_print_str(p, "(");
			p = print_partial_affine_c(p, dim, bset, bset->eq[i],
						   1 + total + j);
			p = isl_printer_print_str(p, ") % ");
			p = isl_printer_print_isl_int(p,
						bset->eq[i][1 + total + j]);
			p = isl_printer_print_str(p, " == 0");
			first = 0;
		}
	}
	for (i = 0; i < bset->n_ineq; ++i)
		p = print_constraint_c(p, dim, bset, bset->ineq[i], ">=",
					&first);
	return p;
}
