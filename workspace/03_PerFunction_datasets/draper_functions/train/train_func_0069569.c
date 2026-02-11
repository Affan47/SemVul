isl_basic_map_domain_map(
	__isl_take isl_basic_map *bmap)
{
	int i, k;
	isl_space *dim;
	isl_basic_map *domain;
	int nparam, n_in, n_out;
	unsigned total;

	nparam = isl_basic_map_dim(bmap, isl_dim_param);
	n_in = isl_basic_map_dim(bmap, isl_dim_in);
	n_out = isl_basic_map_dim(bmap, isl_dim_out);

	dim = isl_space_from_range(isl_space_domain(isl_basic_map_get_space(bmap)));
	domain = isl_basic_map_universe(dim);

	bmap = isl_basic_map_from_domain(isl_basic_map_wrap(bmap));
	bmap = isl_basic_map_apply_range(bmap, domain);
	bmap = isl_basic_map_extend_constraints(bmap, n_in, 0);

	total = isl_basic_map_total_dim(bmap);

	for (i = 0; i < n_in; ++i) {
		k = isl_basic_map_alloc_equality(bmap);
		if (k < 0)
			goto error;
		isl_seq_clr(bmap->eq[k], 1 + total);
		isl_int_set_si(bmap->eq[k][1 + nparam + i], -1);
		isl_int_set_si(bmap->eq[k][1 + nparam + n_in + n_out + i], 1);
	}

	bmap = isl_basic_map_gauss(bmap, NULL);
	return isl_basic_map_finalize(bmap);
error:
	isl_basic_map_free(bmap);
	return NULL;
}
