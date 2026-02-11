vfs_file_eject_callback (GObject *source_object,
			 GAsyncResult *res,
			 gpointer callback_data)
{
	NautilusFileOperation *op;
	gboolean ejected;
	GError *error;

	op = callback_data;

	error = NULL;
	ejected = g_file_eject_mountable_with_operation_finish (G_FILE (source_object),
								res, &error);

	if (!ejected &&
	    error->domain == G_IO_ERROR &&
	    (error->code == G_IO_ERROR_FAILED_HANDLED ||
	     error->code == G_IO_ERROR_CANCELLED)) {
		g_error_free (error);
		error = NULL;
	}

	nautilus_file_operation_complete (op, G_FILE (source_object), error);
	if (error) {
		g_error_free (error);
	}
}
