g_mime_filter_enriched_class_init (GMimeFilterEnrichedClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	GMimeFilterClass *filter_class = GMIME_FILTER_CLASS (klass);
	guint i;

	parent_class = g_type_class_ref (GMIME_TYPE_FILTER);

	object_class->finalize = g_mime_filter_enriched_finalize;

	filter_class->copy = filter_copy;
	filter_class->reset = filter_reset;
	filter_class->filter = filter_filter;
	filter_class->complete = filter_complete;

	if (!enriched_hash) {
		enriched_hash = g_hash_table_new (g_mime_strcase_hash, g_mime_strcase_equal);
		for (i = 0; i < NUM_ENRICHED_TAGS; i++)
			g_hash_table_insert (enriched_hash, enriched_tags[i].enriched,
					     enriched_tags[i].html);
	}
}
