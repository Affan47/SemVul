isl_printer_print_local_space(__isl_take isl_printer *p,
	__isl_keep isl_local_space *ls)
{
	struct isl_print_space_data data = { 0 };
	unsigned n_div;

	if (!ls)
		goto error;

	if (isl_local_space_dim(ls, isl_dim_param) > 0) {
		p = print_tuple(ls->dim, p, isl_dim_param, &data);
		p = isl_printer_print_str(p, " -> ");
	}
	p = isl_printer_print_str(p, "{ ");
	p = print_space(ls->dim, p, 0, &data);
	n_div = isl_local_space_dim(ls, isl_dim_div);
	if (n_div > 0) {
		p = isl_printer_print_str(p, " : ");
		p = isl_printer_print_str(p, s_open_exists[0]);
		p = print_div_list(p, ls->dim, ls->div, 0);
	} else if (isl_space_is_params(ls->dim))
		p = isl_printer_print_str(p, s_such_that[0]);
	p = isl_printer_print_str(p, " }");
	return p;
error:
	isl_printer_free(p);
	return NULL;
}
