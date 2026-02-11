brasero_local_track_start (BraseroJob *job,
			   GError **error)
{
	BraseroLocalTrackPrivate *priv;
	BraseroBurnResult result;
	BraseroJobAction action;
	BraseroLocalTrack *self;
	BraseroTrack *track;
	GSList *grafts;
	gchar *uri;

	self = BRASERO_LOCAL_TRACK (job);
	priv = BRASERO_LOCAL_TRACK_PRIVATE (self);


	brasero_job_get_action (job, &action);
	if (action == BRASERO_JOB_ACTION_SIZE) {

		brasero_job_set_output_size_for_current_track (job, 0, 0);
		return BRASERO_BURN_NOT_RUNNING;
	}

	if (action != BRASERO_JOB_ACTION_IMAGE)
		return BRASERO_BURN_NOT_SUPPORTED;


	brasero_job_get_current_track (job, &track);

	result = BRASERO_BURN_OK;


	if (BRASERO_IS_TRACK_DATA (track)) {

		grafts = brasero_track_data_get_grafts (BRASERO_TRACK_DATA (track));
		for (; grafts; grafts = grafts->next) {
			BraseroGraftPt *graft;

			graft = grafts->data;
			result = brasero_local_track_add_if_non_local (self, graft->uri, error);
			if (result != BRASERO_BURN_OK)
				break;
		}
	}
	else if (BRASERO_IS_TRACK_STREAM (track)) {

		uri = brasero_track_stream_get_source (BRASERO_TRACK_STREAM (track), TRUE);
		result = brasero_local_track_add_if_non_local (self, uri, error);
		g_free (uri);
	}
	else if (BRASERO_IS_TRACK_IMAGE (track)) {

		uri = brasero_track_image_get_source (BRASERO_TRACK_IMAGE (track), TRUE);
		result = brasero_local_track_add_if_non_local (self, uri, error);
		g_free (uri);

		if (result == BRASERO_BURN_OK) {
			priv->download_checksum = TRUE;

			uri = brasero_track_image_get_toc_source (BRASERO_TRACK_IMAGE (track), TRUE);
			result = brasero_local_track_add_if_non_local (self, uri, error);
			g_free (uri);
		}
	}
	else
		BRASERO_JOB_NOT_SUPPORTED (self);

	if (result != BRASERO_BURN_OK)
		return result;


	if (!priv->nonlocals) {
		BRASERO_JOB_LOG (self, "no remote URIs");
		return BRASERO_BURN_NOT_RUNNING;
	}


	g_hash_table_foreach_remove (priv->nonlocals,
				     (GHRFunc) _foreach_non_local_cb,
				     job);

	return brasero_local_track_start_thread (self, error);
}
