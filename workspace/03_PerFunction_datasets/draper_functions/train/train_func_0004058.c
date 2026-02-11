build_context_destroy_view (BuildContext *context)
{
	BasicAutotoolsPlugin* plugin = ANJUTA_PLUGIN_BASIC_AUTOTOOLS (context->plugin);
	if (context->message_view)
	{
		gtk_widget_destroy (GTK_WIDGET (context->message_view));
		context->message_view = NULL;
	}

	if (context->build_dir_stack)
	{
		g_hash_table_destroy (context->build_dir_stack);
		context->build_dir_stack = NULL;
	}
	if (context->indicators_updated_editors)
	{
		g_hash_table_destroy (context->indicators_updated_editors);
		context->indicators_updated_editors = NULL;
	}

	g_slist_foreach (context->locations, (GFunc) build_indicator_location_free,
					 NULL);
	g_slist_free (context->locations);
	context->locations = NULL;


	if (context->launcher == NULL)
	{
		plugin->contexts_pool =
			g_list_remove (plugin->contexts_pool,
			               context);
		g_free (context);
	}
	else
	{

		anjuta_launcher_signal (context->launcher, SIGKILL);
	}

	return TRUE;
}
