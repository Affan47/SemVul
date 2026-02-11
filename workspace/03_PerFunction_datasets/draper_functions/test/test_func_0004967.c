isl_pw_multi_aff_from_map(__isl_take isl_map *map)
{
	int i, j;
	int sv;
	isl_basic_map *hull;
	unsigned n_out;
	unsigned o_out;
	unsigned n_div;
	unsigned o_div;
	isl_int gcd;

	if (!map)
		return NULL;

	hull = isl_map_affine_hull(isl_map_copy(map));
	sv = isl_basic_map_plain_is_single_valued(hull);
	if (sv >= 0 && sv)
		return plain_pw_multi_aff_from_map(isl_map_domain(map), hull);
	if (sv < 0)
		hull = isl_basic_map_free(hull);
	if (!hull)
		goto error;

	n_div = isl_basic_map_dim(hull, isl_dim_div);
	o_div = isl_basic_map_offset(hull, isl_dim_div);

	if (n_div == 0) {
		isl_basic_map_free(hull);
		return pw_multi_aff_from_map_check_div(map);
	}

	isl_int_init(gcd);

	n_out = isl_basic_map_dim(hull, isl_dim_out);
	o_out = isl_basic_map_offset(hull, isl_dim_out);

	for (i = 0; i < n_out; ++i) {
		for (j = 0; j < hull->n_eq; ++j) {
			isl_int *eq = hull->eq[j];
			isl_pw_multi_aff *res;

			if (!isl_int_is_one(eq[o_out + i]) &&
			    !isl_int_is_negone(eq[o_out + i]))
				continue;
			if (isl_seq_first_non_zero(eq + o_out, i) != -1)
				continue;
			if (isl_seq_first_non_zero(eq + o_out + i + 1,
						    n_out - (i + 1)) != -1)
				continue;
			isl_seq_gcd(eq + o_div, n_div, &gcd);
			if (isl_int_is_zero(gcd))
				continue;
			if (isl_int_is_one(gcd))
				continue;

			res = pw_multi_aff_from_map_stride(map, hull,
								i, j, gcd);
			isl_int_clear(gcd);
			return res;
		}
	}

	isl_int_clear(gcd);
	isl_basic_map_free(hull);
	return pw_multi_aff_from_map_check_div(map);
error:
	isl_map_free(map);
	return NULL;
}
