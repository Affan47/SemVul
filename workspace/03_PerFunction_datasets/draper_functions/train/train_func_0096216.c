update (GtkSourceSearchContext *search)
{
	GtkTextIter start;
	GtkTextIter end;

	if (dispose_has_run (search))
	{
		return;
	}

	clear_search (search);
	update_regex (search);

	search->priv->scan_region = gtk_text_region_new (search->priv->buffer);

	gtk_text_buffer_get_bounds (search->priv->buffer, &start, &end);
	add_subregion_to_scan (search, &start, &end);
}
