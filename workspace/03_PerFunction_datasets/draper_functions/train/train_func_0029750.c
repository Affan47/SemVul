smart_backward_search_step (GtkSourceSearchContext *search,
			    GtkTextIter            *start_at,
			    GtkTextIter            *match_start,
			    GtkTextIter            *match_end)
{
	GtkTextIter iter = *start_at;
	GtkTextIter limit;
	GtkTextIter region_end = *start_at;
	GtkTextRegion *region = NULL;

	if (gtk_text_iter_begins_tag (&iter, search->priv->found_tag) ||
	    (!gtk_text_iter_has_tag (&iter, search->priv->found_tag) &&
	     !gtk_text_iter_ends_tag (&iter, search->priv->found_tag)))
	{
		gtk_text_iter_backward_to_tag_toggle (&iter, search->priv->found_tag);
	}
	else if (gtk_text_iter_has_tag (&iter, search->priv->found_tag))
	{
		gtk_text_iter_forward_to_tag_toggle (&iter, search->priv->found_tag);
		region_end = iter;
	}

	limit = iter;
	gtk_text_iter_backward_to_tag_toggle (&limit, search->priv->found_tag);

	if (search->priv->scan_region != NULL)
	{
		region = gtk_text_region_intersect (search->priv->scan_region, &limit, &region_end);
	}

	if (is_text_region_empty (region))
	{
		if (region != NULL)
		{
			gtk_text_region_destroy (region);
		}

		while (basic_backward_search (search, &iter, match_start, match_end, &limit))
		{
			if (gtk_text_iter_compare (match_end, start_at) <= 0)
			{
				return TRUE;
			}

			iter = *match_start;
		}

		*start_at = limit;
		return FALSE;
	}


	if (gtk_source_search_settings_get_regex_enabled (search->priv->settings))
	{
		regex_search_scan_next_chunk (search);
	}
	else
	{
		scan_region_forward (search, region);
	}

	gtk_text_region_destroy (region);

	return FALSE;
}
