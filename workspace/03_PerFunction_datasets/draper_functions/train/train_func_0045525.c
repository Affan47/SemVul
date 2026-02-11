mcp_account_manager_goa_commit (const McpAccountStorage *self,
    const McpAccountManager *am)
{
  McpAccountManagerGoaPrivate *priv = GET_PRIVATE (self);
  gchar *data;
  gsize len;
  GError *error = NULL;

  DEBUG ("Save config to %s", priv->filename);

  data = g_key_file_to_data (priv->store, &len, &error);
  if (data == NULL)
    {
      DEBUG ("Failed to get data from store: %s", error->message);

      g_error_free (error);
      return FALSE;
    }

  if (!g_file_set_contents (priv->filename, data, len, &error))
    {
      DEBUG ("Failed to write file: %s", error->message);

      g_free (data);
      g_error_free (error);
      return FALSE;
    }

  g_free (data);

  return TRUE;
}
