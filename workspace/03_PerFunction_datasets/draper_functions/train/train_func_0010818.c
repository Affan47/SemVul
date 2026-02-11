xmms_xform_plugin_methods_set (xmms_xform_plugin_t *plugin,
                               xmms_xform_methods_t *methods)
{
	g_return_if_fail (plugin);
	g_return_if_fail (plugin->plugin.type == XMMS_PLUGIN_TYPE_XFORM);

	XMMS_DBG ("Registering xform '%s'",
	          xmms_plugin_shortname_get ((xmms_plugin_t *) plugin));

	memcpy (&plugin->methods, methods, sizeof (xmms_xform_methods_t));
}
