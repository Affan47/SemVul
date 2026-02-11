tpaw_account_settings_dup_string (TpawAccountSettings *settings,
    const gchar *param)
{
  GVariant *v;
  gchar *result = NULL;

  if (!tp_strdiff (param, "password") && settings->priv->supports_sasl)
    {
      return g_strdup (settings->priv->password);
    }

  v = tpaw_account_settings_dup (settings, param);
  if (v == NULL)
    return NULL;

  if (g_variant_is_of_type (v, G_VARIANT_TYPE_STRING))
    result = g_variant_dup_string (v, NULL);

  g_variant_unref (v);
  return result;
}
