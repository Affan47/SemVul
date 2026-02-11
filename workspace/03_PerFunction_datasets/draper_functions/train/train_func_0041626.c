found_mount_cb (GObject *source_object,
		GAsyncResult *res,
		gpointer user_data)
{
	FindMountData *data = user_data;
	GMount *mount;

	if (g_cancellable_is_cancelled (data->cancellable)) {
		goto out;
	}

	mount = g_file_find_enclosing_mount_finish (G_FILE (source_object),
						    res,
						    NULL);
	if (mount != NULL) {
		data->mount = mount;
		nautilus_get_x_content_types_for_mount_async (mount,
							      found_content_type_cb,
							      data->cancellable,
							      data);
		return;
	}

	data->slot->details->find_mount_cancellable = NULL;

 out:
	g_object_unref (data->cancellable);
	g_free (data);
}
