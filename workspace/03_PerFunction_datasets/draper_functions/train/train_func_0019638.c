xmms_output_plugin_methods_volume_set (xmms_output_plugin_t *plugin,
                                       xmms_output_t *output,
                                       const gchar *chan, guint val)
{
	gboolean res = FALSE;

	g_return_val_if_fail (output, FALSE);
	g_return_val_if_fail (plugin, FALSE);

	if (plugin->methods.volume_set) {
		res = plugin->methods.volume_set (output, chan, val);
	}

	return res;
}
