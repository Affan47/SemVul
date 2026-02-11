e_attachment_save_async (EAttachment *attachment,
                         GFile *destination,
                         GAsyncReadyCallback callback,
                         gpointer user_data)
{
	SaveContext *save_context;
	GCancellable *cancellable;

	g_return_if_fail (E_IS_ATTACHMENT (attachment));
	g_return_if_fail (G_IS_FILE (destination));

	if (e_attachment_get_loading (attachment)) {
		g_simple_async_report_error_in_idle (
			G_OBJECT (attachment), callback, user_data,
			G_IO_ERROR, G_IO_ERROR_BUSY,
			_("A load operation is already in progress"));
		return;
	}

	if (e_attachment_get_saving (attachment)) {
		g_simple_async_report_error_in_idle (
			G_OBJECT (attachment), callback, user_data,
			G_IO_ERROR, G_IO_ERROR_BUSY,
			_("A save operation is already in progress"));
		return;
	}


	if (attachment->priv->mime_part == NULL) {
		g_simple_async_report_error_in_idle (
			G_OBJECT (attachment), callback, user_data,
			G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
			_("Attachment contents not loaded"));
		return;
	}

	save_context = attachment_save_context_new (
		attachment, callback, user_data);

	cancellable = attachment->priv->cancellable;
	g_cancellable_reset (cancellable);


	g_file_query_info_async (
		destination, G_FILE_ATTRIBUTE_STANDARD_TYPE,
		G_FILE_QUERY_INFO_NONE, G_PRIORITY_DEFAULT,
		cancellable, (GAsyncReadyCallback)
		attachment_save_query_info_cb, save_context);
}
