isl_basic_map_set_tuple_name(
	__isl_take isl_basic_map *bmap, enum isl_dim_type type, const char *s)
{
	bmap = isl_basic_map_cow(bmap);
	if (!bmap)
		return NULL;
	bmap->dim = isl_space_set_tuple_name(bmap->dim, type, s);
	if (!bmap->dim)
		goto error;
	bmap = isl_basic_map_finalize(bmap);
	return bmap;
error:
	isl_basic_map_free(bmap);
	return NULL;
}
