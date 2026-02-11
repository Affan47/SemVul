brasero_track_data_cfg_get_size (BraseroTrack *track,
				 goffset *blocks,
				 goffset *block_size)
{
	BraseroTrackDataCfgPrivate *priv;
	goffset sectors = 0;

	priv = BRASERO_TRACK_DATA_CFG_PRIVATE (track);

	sectors = brasero_data_project_get_sectors (BRASERO_DATA_PROJECT (priv->tree));
	if (blocks) {
		BraseroFileNode *root;
		BraseroImageFS fs_type;
		BraseroFileTreeStats *stats;

		if (!sectors)
			return sectors;

		fs_type = brasero_track_data_cfg_get_fs (BRASERO_TRACK_DATA (track));
		root = brasero_data_project_get_root (BRASERO_DATA_PROJECT (priv->tree));
		stats = BRASERO_FILE_NODE_STATS (root);
		sectors = brasero_data_project_improve_image_size_accuracy (sectors,
									    stats->num_dir,
									    fs_type);
		*blocks = sectors;
	}

	if (block_size)
		*block_size = 2048;

	return BRASERO_BURN_OK;
}
