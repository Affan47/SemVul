brasero_track_data_cfg_iter_has_child (GtkTreeModel *model,
					GtkTreeIter *iter)
{
	BraseroTrackDataCfgPrivate *priv;
	BraseroFileNode *node;

	priv = BRASERO_TRACK_DATA_CFG_PRIVATE (model);


	g_return_val_if_fail (priv->stamp == iter->stamp, FALSE);
	g_return_val_if_fail (iter->user_data != NULL, FALSE);

	if (iter->user_data2 == GINT_TO_POINTER (BRASERO_ROW_BOGUS)) {


		return FALSE;
	}

	node = iter->user_data;


	if (node->is_inserting)
		return FALSE;

	if (node->is_loading)
		return FALSE;

	if (node->is_file)
		return FALSE;


	return TRUE;
}
