isl_basic_map_print_isl(
	__isl_keep isl_basic_map *bmap, __isl_take isl_printer *p,
	int latex)
{
	struct isl_print_space_data data = { .latex = latex };
	int rational = ISL_F_ISSET(bmap, ISL_BASIC_MAP_RATIONAL);

	if (isl_basic_map_dim(bmap, isl_dim_param) > 0) {
		p = print_tuple(bmap->dim, p, isl_dim_param, &data);
		p = isl_printer_print_str(p, " -> ");
	}
	p = isl_printer_print_str(p, "{ ");
	p = print_space(bmap->dim, p, rational, &data);
	p = isl_printer_print_str(p, " : ");
	p = print_disjunct(bmap, bmap->dim, p, latex);
	p = isl_printer_print_str(p, " }");
	return p;
}
