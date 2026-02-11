print_pw_qpolynomial_fold_c(
	__isl_take isl_printer *p, __isl_keep isl_pw_qpolynomial_fold *pwf)
{
	int i;

	if (pwf->n == 1 && isl_set_plain_is_universe(pwf->p[0].set))
		return print_qpolynomial_fold_c(p, pwf->dim, pwf->p[0].fold);

	for (i = 0; i < pwf->n; ++i) {
		p = isl_printer_print_str(p, "(");
		p = print_set_c(p, pwf->dim, pwf->p[i].set);
		p = isl_printer_print_str(p, ") ? (");
		p = print_qpolynomial_fold_c(p, pwf->dim, pwf->p[i].fold);
		p = isl_printer_print_str(p, ") : ");
	}

	p = isl_printer_print_str(p, "0");
	return p;
}
