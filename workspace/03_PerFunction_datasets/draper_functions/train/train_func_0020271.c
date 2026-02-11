eog_job_save_run (EogJob *job)
{
	EogJobSave *save_job;
	GList *it;


	g_return_if_fail (EOG_IS_JOB_SAVE (job));

	g_object_ref (job);


	if (job->error) {
	        g_error_free (job->error);
		job->error = NULL;
	}


	if (eog_job_is_cancelled (job))
		return;

	save_job = EOG_JOB_SAVE (job);

	save_job->current_position = 0;

	for (it = save_job->images; it != NULL; it = it->next, save_job->current_position++) {
		EogImage *image = EOG_IMAGE (it->data);
		EogImageSaveInfo *save_info = NULL;
		gulong handler_id = 0;
		gboolean success = FALSE;

		save_job->current_image = image;


		eog_image_data_ref (image);

		if (!eog_image_has_data (image, EOG_IMAGE_DATA_ALL)) {
			EogImageMetadataStatus m_status;
			gint data2load = 0;

			m_status = eog_image_get_metadata_status (image);
			if (!eog_image_has_data (image, EOG_IMAGE_DATA_IMAGE)) {

				data2load = EOG_IMAGE_DATA_ALL;
			} else if (m_status == EOG_IMAGE_METADATA_NOT_READ)
			{

				data2load = EOG_IMAGE_DATA_EXIF
						| EOG_IMAGE_DATA_XMP;
			}

			if (data2load != 0) {
				eog_image_load (image,
						data2load,
						NULL,
						&job->error);
			}
		}

		handler_id = g_signal_connect (G_OBJECT (image),
						   "save-progress",
							   G_CALLBACK (eog_job_save_progress_callback),
						   job);

		save_info = eog_image_save_info_new_from_image (image);

		success = eog_image_save_by_info (image,
						  save_info,
						  &job->error);

		if (save_info)
			g_object_unref (save_info);

		if (handler_id != 0)
			g_signal_handler_disconnect (G_OBJECT (image), handler_id);

		eog_image_data_unref (image);

		if (!success)
			break;
	}


	g_mutex_lock (job->mutex);


	job->finished = TRUE;


	g_mutex_unlock (job->mutex);


	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE,
			 (GSourceFunc) notify_finished,
			 job,
			 g_object_unref);
}
