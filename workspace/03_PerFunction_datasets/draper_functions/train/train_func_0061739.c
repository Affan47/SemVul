brasero_track_data_cfg_add (BraseroTrackDataCfg *track,
			    const gchar *uri,
			    GtkTreePath *parent)
{
	BraseroTrackDataCfgPrivate *priv;
	BraseroFileNode *parent_node;

	g_return_val_if_fail (BRASERO_TRACK_DATA_CFG (track), FALSE);
	priv = BRASERO_TRACK_DATA_CFG_PRIVATE (track);

	if (priv->loading)
		return FALSE;

	if (parent) {
		parent_node = brasero_track_data_cfg_path_to_node (track, parent);
		if (parent_node && (parent_node->is_file || parent_node->is_loading))
			parent_node = parent_node->parent;
	}
	else
		parent_node = brasero_data_project_get_root (BRASERO_DATA_PROJECT (priv->tree));

	return (brasero_data_project_add_loading_node (BRASERO_DATA_PROJECT (BRASERO_DATA_PROJECT (priv->tree)), uri, parent_node) != NULL);
}
