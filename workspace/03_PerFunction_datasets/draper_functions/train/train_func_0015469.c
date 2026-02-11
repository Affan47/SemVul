brasero_track_data_cfg_remove (BraseroTrackDataCfg *track,
			       GtkTreePath *treepath)
{
	BraseroTrackDataCfgPrivate *priv;
	BraseroFileNode *node;

	g_return_val_if_fail (BRASERO_TRACK_DATA_CFG (track), FALSE);
	priv = BRASERO_TRACK_DATA_CFG_PRIVATE (track);
	if (priv->loading)
		return FALSE;

	node = brasero_track_data_cfg_path_to_node (track, treepath);
	if (!node)
		return FALSE;

	brasero_data_project_remove_node (BRASERO_DATA_PROJECT (priv->tree), node);
	return TRUE;
}
