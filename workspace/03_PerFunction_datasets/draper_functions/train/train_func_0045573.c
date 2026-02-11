isl_basic_map_partial_lexopt(
		struct isl_basic_map *bmap, struct isl_basic_set *dom,
		struct isl_set **empty, int max)
{
	if (!bmap)
		goto error;
	if (bmap->ctx->opt->pip == ISL_PIP_PIP)
		return isl_pip_basic_map_lexopt(bmap, dom, empty, max);
	else
		return isl_tab_basic_map_partial_lexopt(bmap, dom, empty, max);
error:
	isl_basic_map_free(bmap);
	isl_basic_set_free(dom);
	if (empty)
		*empty = NULL;
	return NULL;
}
