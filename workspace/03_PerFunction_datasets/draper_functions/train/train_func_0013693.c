isl_basic_map_lexopt_pw_multi_aff(
	__isl_take isl_basic_map *bmap, int max)
{
	isl_basic_set *dom = NULL;
	isl_space *dom_space;

	if (!bmap)
		goto error;
	dom_space = isl_space_domain(isl_space_copy(bmap->dim));
	dom = isl_basic_set_universe(dom_space);
	return isl_basic_map_partial_lexopt_pw_multi_aff(bmap, dom, NULL, max);
error:
	isl_basic_map_free(bmap);
	return NULL;
}
