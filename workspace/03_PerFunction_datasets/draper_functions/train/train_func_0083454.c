copy_constraint_dim_map(isl_int *dst, isl_int *src,
					struct isl_dim_map *dim_map)
{
	int i;

	for (i = 0; i < dim_map->len; ++i) {
		if (dim_map->m[i].sgn == 0)
			isl_int_set_si(dst[i], 0);
		else if (dim_map->m[i].sgn > 0)
			isl_int_set(dst[i], src[dim_map->m[i].pos]);
		else
			isl_int_neg(dst[i], src[dim_map->m[i].pos]);
	}
}
