dconf_engine_handle_match_rule_sync (DConfEngine *engine,
                                     const gchar *method_name,
                                     const gchar *path)
{
  gint i;


  for (i = 0; i < engine->n_sources; i++)
    {
      GVariant *result;

      if (!engine->sources[i]->bus_type)
        continue;

      result = dconf_engine_dbus_call_sync_func (engine->sources[i]->bus_type, "org.freedesktop.DBus",
                                                 "/org/freedesktop/DBus", "org.freedesktop.DBus", method_name,
                                                 dconf_engine_make_match_rule (engine->sources[i], path),
                                                 G_VARIANT_TYPE_UNIT, NULL);

      if (result)
        g_variant_unref (result);
    }
}
