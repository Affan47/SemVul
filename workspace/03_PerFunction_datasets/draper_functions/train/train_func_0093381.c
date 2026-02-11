_panel_show_handle_error (const gchar  *uri,
			  GdkScreen    *screen,
			  GError       *local_error,
			  GError      **error)
{
	if (local_error == NULL)
		return TRUE;

	else if (g_error_matches (local_error,
				  G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
		g_error_free (local_error);
		return TRUE;
	}

	else if (g_error_matches (local_error,
				  G_IO_ERROR, G_IO_ERROR_NOT_MOUNTED)) {
		GFile *file;
		PanelShowMountOperationHandle *handle;

		handle = g_slice_new (PanelShowMountOperationHandle);
		file = g_file_new_for_uri (uri);


		handle->mount_op = gtk_mount_operation_new (NULL);
		gtk_mount_operation_set_screen (GTK_MOUNT_OPERATION (handle->mount_op),
						screen);
		handle->screen = screen;

		g_file_mount_enclosing_volume (file, G_MOUNT_MOUNT_NONE,
					       handle->mount_op, NULL,
					       _panel_show_mount_async_callback,
					       handle);
		g_object_unref (file);

		return TRUE;
	}

	else if (error != NULL)
		g_propagate_error (error, local_error);

	else {
		_panel_show_error_dialog (uri, screen, local_error->message);
		g_error_free (local_error);
	}

	return FALSE;
}
