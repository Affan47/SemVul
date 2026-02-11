brasero_track_data_add_fs (BraseroTrackData *track,
			   BraseroImageFS fstype)
{
	BraseroTrackDataClass *klass;
	BraseroImageFS fs_before;
	BraseroBurnResult result;

	g_return_val_if_fail (BRASERO_IS_TRACK_DATA (track), BRASERO_BURN_NOT_SUPPORTED);

	fs_before = brasero_track_data_get_fs (track);
	klass = BRASERO_TRACK_DATA_GET_CLASS (track);
	if (!klass->add_fs)
		return BRASERO_BURN_NOT_SUPPORTED;

	result = klass->add_fs (track, fstype);
	if (result != BRASERO_BURN_OK)
		return result;

	if (fs_before != brasero_track_data_get_fs (track))
		brasero_track_changed (BRASERO_TRACK (track));

	return BRASERO_BURN_OK;
}
