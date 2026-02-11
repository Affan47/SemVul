bin_compact(struct st_bin *bin)
{
	g_assert(bin->vals != NULL);

	HREALLOC_ARRAY(bin->vals, bin->nvals);
	bin->nslots = bin->nvals;
}
