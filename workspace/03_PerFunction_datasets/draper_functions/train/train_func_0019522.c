isl_pwf_print_isl_body(
	__isl_take isl_printer *p, __isl_keep isl_pw_qpolynomial_fold *pwf)
{
	int i = 0;

	for (i = 0; i < pwf->n; ++i) {
		if (i)
			p = isl_printer_print_str(p, "; ");
		if (!isl_space_is_params(pwf->p[i].set->dim)) {
			p = print_space(pwf->p[i].set->dim, p, 0, 0, NULL, NULL);
			p = isl_printer_print_str(p, " -> ");
		}
		p = qpolynomial_fold_print(pwf->p[i].fold, p);
		p = print_disjuncts((isl_map *)pwf->p[i].set, p, 0);
	}

	return p;
}
