add_region (GitgDiffView *view, Region *region)
{
	if (view->priv->last_region)
	{
		view->priv->last_region->next = region;
		region->prev = view->priv->last_region;

		if (view->priv->last_region->type == GITG_DIFF_ITER_TYPE_HUNK)
		{
			ensure_max_line (view, (Hunk *)view->priv->last_region);
		}
	}
	else
	{
		view->priv->regions = region;
		region->prev = NULL;
	}

	view->priv->last_region = region;

	if (region->prev && region->prev->type == GITG_DIFF_ITER_TYPE_HEADER)
	{

		hide_header_details (view, region->prev);
	}

	g_sequence_insert_sorted (view->priv->regions_index, region, index_compare, NULL);

	GitgDiffIter iter;
	region_to_iter (view, region, &iter);

	if (region->type == GITG_DIFF_ITER_TYPE_HEADER)
	{
		g_signal_emit (view, diff_view_signals[HEADER_ADDED], 0, &iter);
	}
	else if (region->type == GITG_DIFF_ITER_TYPE_HUNK)
	{
		g_signal_emit (view, diff_view_signals[HUNK_ADDED], 0, &iter);
	}
}
