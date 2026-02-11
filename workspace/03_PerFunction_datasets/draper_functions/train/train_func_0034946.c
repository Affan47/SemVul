_get_session_image_track (BraseroBurnSession *session)
{
	BraseroTrack *track;
	GSList *tracks;
	guint num;

	tracks = brasero_burn_session_get_tracks (session);
	num = g_slist_length (tracks);

	if (num != 1)
		return NULL;

	track = tracks->data;
	if (BRASERO_IS_TRACK_IMAGE (track))
		return track;

	if (BRASERO_IS_TRACK_IMAGE_CFG (track))
		return track;

	return NULL;
}
