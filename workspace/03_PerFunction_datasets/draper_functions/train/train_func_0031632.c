print_div_list(__isl_take isl_printer *p,
	__isl_keep isl_space *space, __isl_keep isl_mat *div, int latex)
{
	int i;
	unsigned n_div;

	if (!p || !space || !div)
		return isl_printer_free(p);

	n_div = isl_mat_rows(div);

	for (i = 0; i < n_div; ++i) {
		if (i)
			p = isl_printer_print_str(p, ", ");
		p = print_name(space, p, isl_dim_div, i, latex);
		if (p->output_format != ISL_FORMAT_ISL ||
		    isl_int_is_zero(div->row[i][0]))
			continue;
		p = isl_printer_print_str(p, " = ");
		p = print_div(space, div, i, p);
	}

	return p;
}
