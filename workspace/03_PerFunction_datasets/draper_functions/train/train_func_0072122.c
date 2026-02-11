print_dim_eq(__isl_take isl_printer *p,
	struct isl_print_space_data *data, unsigned pos)
{
	isl_basic_map *eq = data->user;
	int j;

	j = defining_equality(eq, data->space, data->type, pos);
	if (j >= 0) {
		pos += 1 + isl_space_offset(data->space, data->type);
		p = print_affine_of_len(eq->dim, NULL, p, eq->eq[j], pos);
	} else {
		p = print_name(data->space, p, data->type, pos, data->latex);
	}

	return p;
}
