select_file (ScrapPUpload *self, GtkFileChooser *file_chooser)
{
	GFile *file;
	GError *error = NULL;
	GFileInfo *file_info;
	GDataUploadStream *upload_stream;
	GFileInputStream *file_stream;

	file = gtk_file_chooser_get_file (file_chooser);

	file_info = g_file_query_info (file, G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME "," G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE,
	                               G_FILE_QUERY_INFO_NONE, NULL, NULL);


	upload_stream = gdata_picasaweb_service_upload_file (self->main_data->picasaweb_service, NULL ,
	                                                     self->file, g_file_info_get_display_name (file_info),
	                                                     g_file_info_get_content_type (file_info), NULL, &error);

	g_object_unref (file_info);
	g_object_unref (self->file);
	self->file = NULL;

	if (error != NULL) {
		g_print ("Error: %s\n", error->message);
		g_error_free (error);

		g_object_unref (file);

		return;
	}

	file_stream = g_file_read (file, NULL, NULL);
	g_object_unref (file);

	g_output_stream_splice (G_OUTPUT_STREAM (upload_stream), G_INPUT_STREAM (file_stream),
	                        G_OUTPUT_STREAM_SPLICE_CLOSE_SOURCE | G_OUTPUT_STREAM_SPLICE_CLOSE_TARGET, NULL, NULL);

	self->file = gdata_picasaweb_service_finish_file_upload (self->main_data->picasaweb_service, upload_stream, NULL);

	g_object_unref (file_stream);
	g_object_unref (upload_stream);
}
