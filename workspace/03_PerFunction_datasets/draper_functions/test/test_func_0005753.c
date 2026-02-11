get_tp_account_name (GoaAccount *account)
{
  GHashTable *params = get_tp_parameters (account);
  const char *type = goa_account_get_provider_type (account);
  const char *id = goa_account_get_id (account);
  char *name;

  if (params == NULL)
    return NULL;

  name = g_strdup_printf ("%s/%s/goa_%s_%s",
      (char *) g_hash_table_lookup (params, "manager"),
      (char *) g_hash_table_lookup (params, "protocol"),
      type, id);

  g_hash_table_unref (params);

  return name;
}
