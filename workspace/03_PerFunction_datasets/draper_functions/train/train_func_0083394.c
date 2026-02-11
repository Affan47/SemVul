gitg_diff_view_get_hunk_at_iter (GitgDiffView *view,
                                 GtkTextIter const *iter,
                                 GitgDiffIter *diff_iter)
{
	g_return_val_if_fail (GITG_IS_DIFF_VIEW (view), FALSE);
	g_return_val_if_fail (iter != NULL, FALSE);
	g_return_val_if_fail (diff_iter != NULL, FALSE);

	if (!view->priv->diff_enabled)
	{
		return FALSE;
	}

	ensure_scan (view, gtk_text_iter_get_line (iter));

	Region *region = find_current_region (view, gtk_text_iter_get_line (iter));

	if (region == NULL || region->type != GITG_DIFF_ITER_TYPE_HUNK)
	{
		return FALSE;
	}

	region_to_iter (view, region, diff_iter);
	return TRUE;
}
