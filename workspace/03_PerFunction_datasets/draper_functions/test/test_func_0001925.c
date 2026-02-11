imapx_job_get_message_matches (CamelIMAPXJob *job,
                               CamelFolder *folder,
                               const gchar *uid)
{
	GetMessageData *data;

	data = camel_imapx_job_get_data (job);
	g_return_val_if_fail (data != NULL, FALSE);

	if (!camel_imapx_job_has_folder (job, folder))
		return FALSE;

	if (g_strcmp0 (uid, data->uid) != 0)
		return FALSE;

	return TRUE;
}
