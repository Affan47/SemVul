ViewerOpenStreamCallback (GObject *aObject,
				       GAsyncResult *aRes,
				       void *aData)
{
	totemPlugin *plugin = reinterpret_cast<totemPlugin*>(aData);
	GError *error = NULL;
	GVariant *result;

	g_debug ("OpenStream reply");

	g_object_unref (plugin->mCancellable);
	plugin->mCancellable = NULL;

	result = g_dbus_proxy_call_finish (G_DBUS_PROXY (aObject), aRes, &error);

	if (result == NULL) {
		g_warning ("OpenStream failed: %s", error->message);
		g_error_free (error);
		return;
	}

	g_variant_unref (result);


	if (plugin->mHidden &&
	    plugin->mAutoPlay) {
		plugin->Command (TOTEM_COMMAND_PLAY);
	}
}
