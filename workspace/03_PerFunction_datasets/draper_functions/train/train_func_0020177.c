mcp_account_manager_goa_delete (const McpAccountStorage *self,
    const McpAccountManager *am,
    const gchar *account,
    const gchar *key)
{
  McpAccountManagerGoaPrivate *priv = GET_PRIVATE (self);

  if (!account_is_in_goa (self, account))
    return FALSE;

  DEBUG ("%s: (%s, %s)", G_STRFUNC, account, key);

  if (key == NULL)
    {
      g_key_file_remove_group (priv->store, account, NULL);
    }
  else
    {
      g_key_file_remove_key (priv->store, account, key, NULL);
    }


  return TRUE;
}
