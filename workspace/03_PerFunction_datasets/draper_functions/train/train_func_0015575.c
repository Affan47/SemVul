grl_registry_unregister_source (GrlRegistry *registry,
                                GrlSource *source,
                                GError **error)
{
  gchar *id;
  gboolean ret = TRUE;

  g_return_val_if_fail (GRL_IS_REGISTRY (registry), FALSE);
  g_return_val_if_fail (GRL_IS_SOURCE (source), FALSE);

  g_object_get (source, "source-id", &id, NULL);
  GRL_DEBUG ("Unregistering source '%s'", id);

  if (g_hash_table_remove (registry->priv->sources, id)) {
    GRL_DEBUG ("source '%s' is no longer available", id);
    g_signal_emit (registry, registry_signals[SIG_SOURCE_REMOVED], 0, source);
    g_object_unref (source);
  } else {
    GRL_WARNING ("source '%s' not found", id);
    g_set_error (error,
                 GRL_CORE_ERROR,
                 GRL_CORE_ERROR_UNREGISTER_SOURCE_FAILED,
                 _("Source with id '%s' was not found"), id);
    ret = FALSE;
  }

  g_free (id);
  return ret;
}
