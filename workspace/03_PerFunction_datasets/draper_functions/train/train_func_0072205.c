xls_read_pivot_cache_by_id (XLSReadPivot *s, GsfInfile *container, guint16 n)
{
	BiffQuery *q;
	GsfInput  *cache_stream, *dir;
	char name[5];

	if (NULL == container)
		return;
	dir = gsf_infile_child_by_name (container, "_SX_DB_CUR");
	if (NULL == dir)
		dir = gsf_infile_child_by_name (container, "_SX_DB");
	if (NULL == dir)
		return;

	snprintf (name, sizeof (name), "%04hX", n);
	cache_stream = gsf_infile_child_by_name (GSF_INFILE (dir), name);
	if (NULL != cache_stream) {
		q = ms_biff_query_new (cache_stream);
		d (0, g_printerr ("{ /* PIVOT CACHE [%s] */\n", name););
		if (!xls_read_pivot_cache (s, q)) {
			g_object_unref (s->cache);
			s->cache = NULL;
		} else
			d (2, go_data_cache_dump (s->cache, NULL, NULL););
		d (0, g_printerr ("}; /* PIVOT CACHE [%s] */\n", name););

		ms_biff_query_destroy (q);
		g_object_unref (cache_stream);
	}
	g_object_unref (dir);
}
