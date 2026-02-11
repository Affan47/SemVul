g3d_plugins_load_model_from_stream(G3DContext *context,
	G3DStream *stream, G3DModel *model)
{
	G3DPlugin *plugin = NULL;

	g_return_val_if_fail(stream != NULL, FALSE);

	plugin = get_plugin_for_type(context, stream->uri);
	if(plugin == NULL)
		return FALSE;

	if((plugin->loadmodelstream_func != NULL) && plugin->loadmodelstream_func(
		context, stream, model, plugin->user_data)) {
		model->plugin = plugin;
		return TRUE;
	}
	return FALSE;
}
