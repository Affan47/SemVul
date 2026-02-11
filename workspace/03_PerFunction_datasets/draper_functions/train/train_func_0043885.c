grl_config_get_binary (GrlConfig *config, const gchar *param, gsize *size)
{
  gchar *encoded;
  gsize s;
  guint8 *binary;

  g_return_val_if_fail (GRL_IS_CONFIG (config), NULL);

  encoded = g_key_file_get_string (config->priv->config, GROUP_NAME, param, NULL);
  if (!encoded) {
    return NULL;
  }

  binary = g_base64_decode (encoded, &s);
  g_free (encoded);
  if (size) {
    *size = s;
  }

  return binary;
}
