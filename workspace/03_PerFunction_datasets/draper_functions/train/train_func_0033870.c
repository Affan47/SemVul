regex_search_handle_high_priority_region (GtkSourceSearchContext *search)
{
	GtkTextIter start;
	GtkTextIter end;
	GtkTextRegion *region;
	GtkTextRegionIterator region_iter;
	gint nb_subregions = gtk_text_region_subregions (search->priv->high_priority_region);

	if (nb_subregions == 0)
	{
		return;
	}

	gtk_text_region_nth_subregion (search->priv->high_priority_region,
				       0,
				       &start,
				       NULL);

	gtk_text_region_nth_subregion (search->priv->high_priority_region,
				       nb_subregions - 1,
				       NULL,
				       &end);

	region = gtk_text_region_intersect (search->priv->scan_region,
					    &start,
					    &end);

	gtk_text_region_get_iterator (region, &region_iter, 0);

	while (!gtk_text_region_iterator_is_end (&region_iter))
	{
		GtkTextIter subregion_start;
		GtkTextIter subregion_end;

		gtk_text_region_iterator_get_subregion (&region_iter,
							&subregion_start,
							&subregion_end);

		gtk_text_buffer_remove_tag (search->priv->buffer,
					    search->priv->found_tag,
					    &subregion_start,
					    &subregion_end);

		gtk_text_region_iterator_next (&region_iter);
	}

	gtk_text_region_destroy (region);
}
