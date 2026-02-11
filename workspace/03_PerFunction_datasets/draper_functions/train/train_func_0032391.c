brasero_transcode_send_volume_event (BraseroTranscode *transcode)
{
	BraseroTranscodePrivate *priv;
	gdouble track_peak = 0.0;
	gdouble track_gain = 0.0;
	GstTagList *tag_list;
	BraseroTrack *track;
	GstEvent *event;
	GValue *value;

	priv = BRASERO_TRANSCODE_PRIVATE (transcode);

	brasero_job_get_current_track (BRASERO_JOB (transcode), &track);

	BRASERO_JOB_LOG (transcode, "Sending audio levels tags");
	if (brasero_track_tag_lookup (track, BRASERO_TRACK_PEAK_VALUE, &value) == BRASERO_BURN_OK)
		track_peak = g_value_get_double (value);

	if (brasero_track_tag_lookup (track, BRASERO_TRACK_GAIN_VALUE, &value) == BRASERO_BURN_OK)
		track_gain = g_value_get_double (value);


	tag_list = gst_tag_list_new (GST_TAG_TRACK_GAIN, track_gain,
				     GST_TAG_TRACK_PEAK, track_peak,
				     NULL);


	event = gst_event_new_tag (tag_list);
	if (!gst_element_send_event (priv->convert, event))
		BRASERO_JOB_LOG (transcode, "Couldn't send tags to rgvolume");

	BRASERO_JOB_LOG (transcode, "Set volume level %lf %lf", track_gain, track_peak);
}
