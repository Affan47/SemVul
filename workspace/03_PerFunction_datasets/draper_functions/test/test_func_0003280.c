subversion_ivcs_checkout (IAnjutaVcs *obj,
						  const gchar *repository_location, GFile *dest,
						  GCancellable *cancel,
						  AnjutaAsyncNotify *notify, GError **err)
{
	GError *error;
	gchar *path;
	SvnCheckoutCommand *checkout_command;
	Subversion *plugin;

	error = NULL;
	g_file_make_directory (dest, NULL, &error);
	if (error)
	{
		if (error->code != G_IO_ERROR_EXISTS)
		{
			g_propagate_error (err, error);
			return;
		}
		g_error_free (error);
	}

	path = g_file_get_path (dest);
	checkout_command = svn_checkout_command_new (repository_location, path);
	plugin = ANJUTA_PLUGIN_SUBVERSION (obj);

	g_free (path);

	create_message_view (plugin);

	g_signal_connect (G_OBJECT (checkout_command), "data-arrived",
					  G_CALLBACK (on_command_info_arrived),
					  plugin);

	g_signal_connect (G_OBJECT (checkout_command), "command-finished",
	                  G_CALLBACK (g_object_unref),
	                  NULL);

	if (cancel)
	{
		g_signal_connect_swapped (G_OBJECT (cancel), "cancelled",
								  G_CALLBACK (anjuta_command_cancel),
								  checkout_command);
	}

	if (notify)
	{
		g_signal_connect_swapped (G_OBJECT (checkout_command),
								  "command-finished",
								  G_CALLBACK (anjuta_async_notify_notify_finished),
								  notify);
	}

	anjuta_command_start (ANJUTA_COMMAND (checkout_command));
}
