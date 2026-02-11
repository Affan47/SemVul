brasero_track_data_cfg_virtual_sibling_cb (BraseroDataProject *project,
					   BraseroFileNode *node,
					   BraseroFileNode *sibling,
					   BraseroTrackDataCfg *self)
{
	BraseroTrackDataCfgPrivate *priv;

	priv = BRASERO_TRACK_DATA_CFG_PRIVATE (self);
	if (sibling == priv->icon) {


		priv->icon = node;
	}
}
