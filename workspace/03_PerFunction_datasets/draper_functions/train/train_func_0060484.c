print_nested_tuple(__isl_take isl_printer *p,
	__isl_keep isl_space *local_dim, enum isl_dim_type local_type,
	struct isl_print_space_data *data, int offset)
{
	const char *name = NULL;
	unsigned n = isl_space_dim(local_dim, local_type);
	if ((local_type == isl_dim_in || local_type == isl_dim_out)) {
		name = isl_space_get_tuple_name(local_dim, local_type);
		if (name) {
			if (data->latex)
				p = isl_printer_print_str(p, "\\mathrm{");
			p = isl_printer_print_str(p, name);
			if (data->latex)
				p = isl_printer_print_str(p, "}");
		}
	}
	if (!data->latex || n != 1 || name)
		p = isl_printer_print_str(p, s_open_list[data->latex]);
	if ((local_type == isl_dim_in || local_type == isl_dim_out) &&
	    local_dim->nested[local_type - isl_dim_in]) {
		if (data->space != local_dim && local_type == isl_dim_out)
			offset += local_dim->n_in;
		p = print_nested_map_dim(p,
				local_dim->nested[local_type - isl_dim_in],
				data, offset);
	} else
		p = print_nested_var_list(p, local_dim, local_type, data,
					  offset);
	if (!data->latex || n != 1 || name)
		p = isl_printer_print_str(p, s_close_list[data->latex]);
	return p;
}
