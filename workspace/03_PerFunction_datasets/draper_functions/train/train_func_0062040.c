totem_plugin_stream_as_file (NPP instance,
			     NPStream *stream,
			     const char* fname)
{
	if (!instance)
		return;

	totemPlugin *plugin = reinterpret_cast<totemPlugin*> (instance->pdata);
	if (!plugin)
		return;

	plugin->StreamAsFile (stream, fname);
}
