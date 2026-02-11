brasero_track_data_cfg_iter_next (GtkTreeModel *model,
				   GtkTreeIter *iter)
{
	BraseroTrackDataCfgPrivate *priv;
	BraseroFileNode *node;

	priv = BRASERO_TRACK_DATA_CFG_PRIVATE (model);


	g_return_val_if_fail (priv->stamp == iter->stamp, FALSE);
	g_return_val_if_fail (iter->user_data != NULL, FALSE);

	if (iter->user_data2 == GINT_TO_POINTER (BRASERO_ROW_BOGUS)) {


		iter->user_data = NULL;
		return FALSE;
	}

	node = iter->user_data;
	node = node->next;


	while (node && node->is_hidden)
		node = node->next;

	if (!node || node->is_hidden)
		return FALSE;

	iter->user_data = node;
	return TRUE;
}
