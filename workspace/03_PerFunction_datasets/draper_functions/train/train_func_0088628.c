print_aff_body(__isl_take isl_printer *p,
	__isl_keep isl_aff *aff)
{
	unsigned total;

	total = isl_local_space_dim(aff->ls, isl_dim_all);
	p = isl_printer_print_str(p, "(");
	p = print_affine_of_len(aff->ls->dim, aff->ls->div, p,
				aff->v->el + 1, 1 + total);
	if (isl_int_is_one(aff->v->el[0]))
		p = isl_printer_print_str(p, ")");
	else {
		p = isl_printer_print_str(p, ")/");
		p = isl_printer_print_isl_int(p, aff->v->el[0]);
	}

	return p;
}
