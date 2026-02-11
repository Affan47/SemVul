brasero_track_data_cfg_get_filtered_model (BraseroTrackDataCfg *track)
{
	BraseroTrackDataCfgPrivate *priv;
	GtkTreeModel *model;

	g_return_val_if_fail (BRASERO_TRACK_DATA_CFG (track), NULL);
	priv = BRASERO_TRACK_DATA_CFG_PRIVATE (track);
	model = GTK_TREE_MODEL (brasero_data_vfs_get_filtered_model (BRASERO_DATA_VFS (priv->tree)));
	g_object_ref (model);
	return model;
}
