qam_metadata_ready_cb (GObject      *source_object,
                       GAsyncResult *result,
                       gpointer      user_data)
{
	QueryAllMetadata *qam = user_data;
	GList            *files;
	GError           *error = NULL;

	files = _g_query_metadata_finish (result, &error);
	if (files != NULL)
		qam->ready_func (files, NULL, qam->user_data);
	else
		qam->ready_func (NULL, error, qam->user_data);

	query_all_metadata_free (qam);
}
