move_last(__isl_take isl_basic_map *bmap,
	enum isl_dim_type type, unsigned first, unsigned n)
{
	struct isl_dim_map *dim_map;
	struct isl_basic_map *res;
	enum isl_dim_type t;
	unsigned total, off;

	if (!bmap)
		return NULL;
	if (pos(bmap->dim, type) + first + n ==
				1 + isl_space_dim(bmap->dim, isl_dim_all))
		return bmap;

	total = isl_basic_map_total_dim(bmap);
	dim_map = isl_dim_map_alloc(bmap->ctx, total);

	off = 0;
	for (t = isl_dim_param; t <= isl_dim_out; ++t) {
		unsigned size = isl_space_dim(bmap->dim, t);
		if (t == type) {
			isl_dim_map_dim_range(dim_map, bmap->dim, t,
					    0, first, off);
			off += first;
			isl_dim_map_dim_range(dim_map, bmap->dim, t,
					    first, n, total - bmap->n_div - n);
			isl_dim_map_dim_range(dim_map, bmap->dim, t,
					    first + n, size - (first + n), off);
			off += size - (first + n);
		} else {
			isl_dim_map_dim(dim_map, bmap->dim, t, off);
			off += size;
		}
	}
	isl_dim_map_div(dim_map, bmap, off + n);

	res = isl_basic_map_alloc_space(isl_basic_map_get_space(bmap),
			bmap->n_div, bmap->n_eq, bmap->n_ineq);
	res = isl_basic_map_add_constraints_dim_map(res, bmap, dim_map);
	return res;
}
