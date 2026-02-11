print_name_c(__isl_take isl_printer *p,
	__isl_keep isl_space *dim,
	__isl_keep isl_basic_set *bset, enum isl_dim_type type, unsigned pos)
{
	if (type == isl_dim_div) {
		p = isl_printer_print_str(p, "floord(");
		p = print_affine_c(p, dim, bset, bset->div[pos] + 1);
		p = isl_printer_print_str(p, ", ");
		p = isl_printer_print_isl_int(p, bset->div[pos][0]);
		p = isl_printer_print_str(p, ")");
	} else {
		const char *name;

		name = isl_space_get_dim_name(dim, type, pos);
		if (!name)
			name = "UNNAMED";
		p = isl_printer_print_str(p, name);
	}
	return p;
}
