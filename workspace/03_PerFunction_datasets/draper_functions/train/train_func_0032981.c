gal_view_etable_detach (GalViewEtable *view)
{
	g_return_if_fail (GAL_IS_VIEW_ETABLE (view));

	if (view->priv->table != NULL)
		detach_table (view);
	if (view->priv->tree != NULL)
		detach_tree (view);
}
