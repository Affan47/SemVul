brasero_transcode_get_duration (BraseroTranscode *transcode)
{
	gint64 duration = -1;
	BraseroTranscodePrivate *priv;

	priv = BRASERO_TRANSCODE_PRIVATE (transcode);


	if (priv->mp3_size_pipeline) {


		gst_element_query_position (priv->pipeline,
					    GST_FORMAT_TIME,
					    &duration);
	}


	if (duration == -1 || duration == 0)
		gst_element_query_duration (priv->pipeline,
					    GST_FORMAT_TIME,
					    &duration);

	BRASERO_JOB_LOG (transcode, "got duration %" GST_TIME_FORMAT, GST_TIME_ARGS (duration));

	if (duration == -1 || duration == 0)
	    brasero_job_error (BRASERO_JOB (transcode),
			       g_error_new (BRASERO_BURN_ERROR,
					    BRASERO_BURN_ERROR_GENERAL, "%s",
					    _("Error while getting duration")));
	return duration;
}
