plugin_loader_create_blacklist_plugin (GstPluginLoader * l,
    PendingPluginEntry * entry)
{
  GstPlugin *plugin = g_object_newv (GST_TYPE_PLUGIN, 0, NULL);

  plugin->filename = g_strdup (entry->filename);
  plugin->file_mtime = entry->file_mtime;
  plugin->file_size = entry->file_size;
  GST_OBJECT_FLAG_SET (plugin, GST_PLUGIN_FLAG_BLACKLISTED);

  plugin->basename = g_path_get_basename (plugin->filename);
  plugin->desc.name = g_intern_string (plugin->basename);
  plugin->desc.description = "Plugin for blacklisted file";
  plugin->desc.version = "0.0.0";
  plugin->desc.license = "BLACKLIST";
  plugin->desc.source = plugin->desc.license;
  plugin->desc.package = plugin->desc.license;
  plugin->desc.origin = plugin->desc.license;

  GST_DEBUG ("Adding blacklist plugin '%s'", plugin->desc.name);
  gst_registry_add_plugin (l->registry, plugin);
}
