dconf_settings_backend_read (GSettingsBackend   *backend,
                             const gchar        *key,
                             const GVariantType *expected_type,
                             gboolean            default_value)
{
  DConfSettingsBackend *dcsb = (DConfSettingsBackend *) backend;
  GVariant *value;

  if (default_value)
    {
      GQueue *read_through;


      read_through = g_queue_new ();
      g_queue_push_tail (read_through, dconf_changeset_new_write (key, NULL));
      value = dconf_engine_read (dcsb->engine, read_through, key);
      g_queue_free_full (read_through, (GDestroyNotify) dconf_changeset_unref);
    }

  else
    value = dconf_engine_read (dcsb->engine, NULL, key);

  return value;
}
