isl_basic_map_insert_dims(
	__isl_take isl_basic_map *bmap, enum isl_dim_type type,
	unsigned pos, unsigned n)
{
	isl_space *res_dim;
	struct isl_basic_map *res;
	struct isl_dim_map *dim_map;
	unsigned total, off;
	enum isl_dim_type t;

	if (n == 0)
		return basic_map_space_reset(bmap, type);

	if (!bmap)
		return NULL;

	res_dim = isl_space_insert_dims(isl_basic_map_get_space(bmap), type, pos, n);

	total = isl_basic_map_total_dim(bmap) + n;
	dim_map = isl_dim_map_alloc(bmap->ctx, total);
	off = 0;
	for (t = isl_dim_param; t <= isl_dim_out; ++t) {
		if (t != type) {
			isl_dim_map_dim(dim_map, bmap->dim, t, off);
		} else {
			unsigned size = isl_basic_map_dim(bmap, t);
			isl_dim_map_dim_range(dim_map, bmap->dim, t,
						0, pos, off);
			isl_dim_map_dim_range(dim_map, bmap->dim, t,
						pos, size - pos, off + pos + n);
		}
		off += isl_space_dim(res_dim, t);
	}
	isl_dim_map_div(dim_map, bmap, off);

	res = isl_basic_map_alloc_space(res_dim,
			bmap->n_div, bmap->n_eq, bmap->n_ineq);
	if (isl_basic_map_is_rational(bmap))
		res = isl_basic_map_set_rational(res);
	if (isl_basic_map_plain_is_empty(bmap)) {
		isl_basic_map_free(bmap);
		free(dim_map);
		return isl_basic_map_set_to_empty(res);
	}
	res = isl_basic_map_add_constraints_dim_map(res, bmap, dim_map);
	return isl_basic_map_finalize(res);
}
