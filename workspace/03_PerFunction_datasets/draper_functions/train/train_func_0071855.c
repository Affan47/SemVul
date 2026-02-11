cg_plugin_generator_created_cb (CgGenerator *generator,
                                gpointer user_data)
{
	AnjutaClassGenPlugin *plugin;
	const gchar *header_file;
	const gchar *source_file;
	IAnjutaFileLoader *loader;

	plugin = (AnjutaClassGenPlugin *) user_data;
	header_file = cg_generator_get_header_destination (generator);
	source_file = cg_generator_get_source_destination (generator);

	loader = anjuta_shell_get_interface (ANJUTA_PLUGIN (plugin)->shell,
	                                     IAnjutaFileLoader, NULL);

	if (cg_window_get_add_to_project (plugin->window))
	{
		GFile* header = NULL;
		GFile* source = g_file_new_for_path (source_file);
		IAnjutaProjectManager *manager;


		if (header_file == NULL)
		{
			ianjuta_file_loader_load (loader, source, FALSE, NULL);
		}
		else
		{
			header = g_file_new_for_path (header_file);
			ianjuta_file_loader_load (loader, header, FALSE, NULL);
			ianjuta_file_loader_load (loader, source, FALSE, NULL);
		}

		if (cg_window_get_add_to_repository (plugin->window))
		{
			cg_plugin_add_to_repository (plugin, header, source);
		}

		manager = anjuta_shell_get_interface (ANJUTA_PLUGIN (plugin)->shell, IAnjutaProjectManager, NULL);
		if (manager)
		{
			if (header == NULL)
			{
			    g_signal_emit_by_name (G_OBJECT (manager), "element_added", source);
			}
			else
			{
			    g_signal_emit_by_name (G_OBJECT (manager), "element_added", header);
			    g_signal_emit_by_name (G_OBJECT (manager), "element_added", source);
			}

		}

		if (header != NULL) g_object_unref (header);
		g_object_unref (source);
	}
	else
	{
		if (header_file == NULL)
		{


			cg_plugin_load (plugin, generator, source_file, NULL);
		}
		else
		{
			cg_plugin_load (plugin, generator, header_file, NULL);
			cg_plugin_load (plugin, generator, source_file, NULL);
		}
	}

	g_object_unref (G_OBJECT (plugin->window));
	plugin->window = NULL;
}
