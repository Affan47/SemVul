gst_registry_chunks_load_plugin_dep (GstPlugin * plugin, gchar ** in,
    gchar * end)
{
  GstPluginDep *dep;
  GstRegistryChunkDep *d;
  gchar **s;

  align (*in);
  GST_LOG_OBJECT (plugin, "Unpacking GstRegistryChunkDep from %p", *in);
  unpack_element (*in, d, GstRegistryChunkDep, end, fail);

  dep = g_slice_new (GstPluginDep);

  dep->env_hash = d->env_hash;
  dep->stat_hash = d->stat_hash;

  dep->flags = (GstPluginDependencyFlags) d->flags;

  dep->names = gst_registry_chunks_load_plugin_dep_strv (in, end, d->n_names);
  dep->paths = gst_registry_chunks_load_plugin_dep_strv (in, end, d->n_paths);
  dep->env_vars =
      gst_registry_chunks_load_plugin_dep_strv (in, end, d->n_env_vars);

  plugin->priv->deps = g_list_append (plugin->priv->deps, dep);

  GST_DEBUG_OBJECT (plugin, "Loaded external plugin dependency from registry: "
      "env_hash: %08x, stat_hash: %08x", dep->env_hash, dep->stat_hash);
  for (s = dep->env_vars; s != NULL && *s != NULL; ++s)
    GST_LOG_OBJECT (plugin, " evar: %s", *s);
  for (s = dep->paths; s != NULL && *s != NULL; ++s)
    GST_LOG_OBJECT (plugin, " path: %s", *s);
  for (s = dep->names; s != NULL && *s != NULL; ++s)
    GST_LOG_OBJECT (plugin, " name: %s", *s);

  return TRUE;
fail:
  GST_INFO ("Reading plugin dependency failed");
  return FALSE;
}
