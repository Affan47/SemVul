sourceview_io_get_read_only (SourceviewIO* sio)
{
	GFileInfo* file_info;
	gboolean retval;

	if (!sio->file)
		return FALSE;

	file_info = g_file_query_info (sio->file,
								   G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE,
								   G_FILE_QUERY_INFO_NONE,
								   NULL,
								   NULL);
	if (!file_info)
		return FALSE;

	retval = !g_file_info_get_attribute_boolean (file_info,
												G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE);
	g_object_unref (file_info);
	return retval;
}
