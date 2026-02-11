brasero_transcode_create_sibling_image (BraseroTranscode *transcode,
					BraseroTrack *src,
					GError **error)
{
	BraseroTrackStream *dest;
	BraseroTrack *track;
	guint64 length = 0;
	gchar *path_dest;
	gchar *path_src;


	path_src = brasero_track_stream_get_source (BRASERO_TRACK_STREAM (src), FALSE);
	brasero_job_get_audio_output (BRASERO_JOB (transcode), &path_dest);

	if (symlink (path_src, path_dest) == -1) {
                int errsv = errno;

		g_set_error (error,
			     BRASERO_BURN_ERROR,
			     BRASERO_BURN_ERROR_GENERAL,

			     _("An internal error occurred (%s)"),
			     g_strerror (errsv));

		goto error;
	}

	dest = brasero_track_stream_new ();
	brasero_track_stream_set_source (dest, path_dest);


	brasero_track_stream_set_format (dest, BRASERO_AUDIO_FORMAT_RAW);


	brasero_track_stream_get_length (BRASERO_TRACK_STREAM (src), &length);
	brasero_track_stream_set_boundaries (dest, 0, length, 0);


	brasero_job_get_current_track (BRASERO_JOB (transcode), &track);
	brasero_track_tag_copy_missing (BRASERO_TRACK (dest), track);
	brasero_job_add_track (BRASERO_JOB (transcode), BRASERO_TRACK (dest));


	g_object_unref (dest);

	g_free (path_src);
	g_free (path_dest);

	return BRASERO_BURN_NOT_RUNNING;

error:
	g_free (path_src);
	g_free (path_dest);

	return BRASERO_BURN_ERR;
}
