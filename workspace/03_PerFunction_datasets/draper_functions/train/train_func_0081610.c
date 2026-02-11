test_highlight (void)
{
	GtkSourceBuffer *source_buffer = gtk_source_buffer_new (NULL);
	GtkSourceSearchContext *context1 = gtk_source_search_context_new (source_buffer, NULL);
	GtkSourceSearchContext *context2 = gtk_source_search_context_new (source_buffer, NULL);
	gboolean highlight;

	gtk_source_search_context_set_highlight (context1, TRUE);
	highlight = gtk_source_search_context_get_highlight (context1);
	g_assert (highlight);

	gtk_source_search_context_set_highlight (context2, FALSE);
	highlight = gtk_source_search_context_get_highlight (context2);
	g_assert (!highlight);

	g_object_unref (source_buffer);
	g_object_unref (context1);
	g_object_unref (context2);
}
