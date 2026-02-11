test_vertices(isl_ctx *ctx)
{
	const char *str;
	isl_basic_set *bset;
	isl_vertices *vertices;

	str = "{ A[t, i] : t = 12 and i >= 4 and i <= 12 }";
	bset = isl_basic_set_read_from_str(ctx, str);
	vertices = isl_basic_set_compute_vertices(bset);
	isl_basic_set_free(bset);
	isl_vertices_free(vertices);
	if (!vertices)
		return -1;

	str = "{ A[t, i] : t = 14 and i = 1 }";
	bset = isl_basic_set_read_from_str(ctx, str);
	vertices = isl_basic_set_compute_vertices(bset);
	isl_basic_set_free(bset);
	isl_vertices_free(vertices);
	if (!vertices)
		return -1;

	return 0;
}
