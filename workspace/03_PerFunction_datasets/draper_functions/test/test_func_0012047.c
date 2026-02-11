set_up_substitutions(
	__isl_keep isl_basic_map *bmap_i, __isl_keep isl_basic_map *bmap_j,
	__isl_take isl_basic_map *hull)
{
	unsigned n_div_i, n_div_j, total;
	isl_ctx *ctx;
	isl_local_space *ls;
	isl_basic_set *wrap_hull;
	isl_aff *aff_nan;
	isl_aff_list *list;
	int i, j;

	if (!hull)
		return NULL;

	ctx = isl_basic_map_get_ctx(hull);

	n_div_i = isl_basic_map_dim(bmap_i, isl_dim_div);
	n_div_j = isl_basic_map_dim(bmap_j, isl_dim_div);
	total = isl_basic_map_total_dim(bmap_i) - n_div_i;

	ls = isl_basic_map_get_local_space(bmap_i);
	ls = isl_local_space_wrap(ls);
	wrap_hull = isl_basic_map_wrap(hull);

	aff_nan = isl_aff_nan_on_domain(isl_local_space_copy(ls));
	list = isl_aff_list_alloc(ctx, n_div_i);

	j = 0;
	for (i = 0; i < n_div_i; ++i) {
		isl_aff *aff;

		if (j < n_div_j &&
		    isl_seq_eq(bmap_i->div[i], bmap_j->div[j], 2 + total)) {
			++j;
			list = isl_aff_list_add(list, isl_aff_copy(aff_nan));
			continue;
		}
		if (n_div_i - i <= n_div_j - j)
			break;

		aff = isl_local_space_get_div(ls, i);
		aff = isl_aff_substitute_equalities(aff,
						isl_basic_set_copy(wrap_hull));
		aff = isl_aff_floor(aff);
		if (!aff)
			goto error;
		if (isl_aff_dim(aff, isl_dim_div) != 0) {
			isl_aff_free(aff);
			break;
		}

		list = isl_aff_list_add(list, aff);
	}

	isl_aff_free(aff_nan);
	isl_local_space_free(ls);
	isl_basic_set_free(wrap_hull);

	return list;
error:
	isl_aff_free(aff_nan);
	isl_local_space_free(ls);
	isl_basic_set_free(wrap_hull);
	isl_aff_list_free(list);
	return NULL;
}
