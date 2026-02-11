model_mount_root (GeditFileBrowserStore *model,
		  GFile                 *virtual_root)
{
	GFileInfo *info;
	GError *error = NULL;
	MountInfo *mount_info;

	info = g_file_query_info (model->priv->root->file,
				  G_FILE_ATTRIBUTE_STANDARD_TYPE,
				  G_FILE_QUERY_INFO_NONE,
				  NULL,
				  &error);

	if (!info)
	{
		if (error->code == G_IO_ERROR_NOT_MOUNTED)
		{

			FILE_BROWSER_NODE_DIR (model->priv->root)->cancellable = g_cancellable_new ();

			mount_info = g_slice_new (MountInfo);
			mount_info->model = model;
			mount_info->virtual_root = g_file_dup (virtual_root);


			mount_info->operation = gtk_mount_operation_new (NULL);
			mount_info->cancellable = g_object_ref (FILE_BROWSER_NODE_DIR (model->priv->root)->cancellable);

			model_begin_loading (model, model->priv->root);
			g_file_mount_enclosing_volume (model->priv->root->file,
						       G_MOUNT_MOUNT_NONE,
						       mount_info->operation,
						       mount_info->cancellable,
						       (GAsyncReadyCallback)mount_cb,
						       mount_info);

			model->priv->mount_info = mount_info;
			return GEDIT_FILE_BROWSER_STORE_RESULT_MOUNTING;
		}
		else
		{
			handle_root_error (model, error);
		}

		g_error_free (error);
	}
	else
	{
		g_object_unref (info);

		return model_root_mounted (model, virtual_root);
	}

	return GEDIT_FILE_BROWSER_STORE_RESULT_OK;
}
