gconf_settings_backend_read (GSettingsBackend   *backend,
                             const gchar        *key,
                             const GVariantType *expected_type,
                             gboolean            default_value)
{
  GConfSettingsBackend *gconf = GCONF_SETTINGS_BACKEND (backend);
  GConfValue *gconf_value;
  GVariant *value;

  gconf_value = gconf_client_get_without_default (gconf->priv->client,
                                                  key, NULL);
  if (gconf_value == NULL)
    return NULL;

  value = gconf_settings_backend_gconf_value_to_gvariant (gconf_value, expected_type);
  gconf_value_free (gconf_value);

  if (value != NULL)
    g_variant_ref_sink (value);

  return value;
}
