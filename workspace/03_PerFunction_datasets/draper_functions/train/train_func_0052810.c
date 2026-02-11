camel_imapx_server_refresh_info (CamelIMAPXServer *is,
                                 CamelFolder *folder,
                                 GCancellable *cancellable,
                                 GError **error)
{
	CamelIMAPXJob *job;
	RefreshInfoData *data;
	gboolean registered = TRUE;
	const gchar *full_name;
	gboolean success = TRUE;

	full_name = camel_folder_get_full_name (folder);

	QUEUE_LOCK (is);


	if (imapx_is_job_in_queue (is, folder, IMAPX_JOB_REFRESH_INFO, NULL) ||
		imapx_is_job_in_queue (is, folder, IMAPX_JOB_FETCH_MESSAGES, NULL)) {
		QUEUE_UNLOCK (is);
		return TRUE;
	}

	data = g_slice_new0 (RefreshInfoData);
	data->changes = camel_folder_change_info_new ();

	job = camel_imapx_job_new (cancellable);
	job->type = IMAPX_JOB_REFRESH_INFO;
	job->start = imapx_job_refresh_info_start;
	job->matches = imapx_job_refresh_info_matches;
	job->pri = IMAPX_PRIORITY_REFRESH_INFO;

	camel_imapx_job_set_folder (job, folder);

	if (g_ascii_strcasecmp (full_name, "INBOX") == 0)
		job->pri += 10;

	camel_imapx_job_set_data (
		job, data, (GDestroyNotify) refresh_info_data_free);

	registered = imapx_register_job (is, job, error);

	QUEUE_UNLOCK (is);

	success = registered && camel_imapx_job_run (job, is, error);

	if (success && camel_folder_change_info_changed (data->changes))
		camel_folder_changed (folder, data->changes);

	camel_imapx_job_unref (job);

	return success;
}
