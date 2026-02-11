gconf_client_key_is_writable (GConfClient* client,
                              const gchar* key,
                              GError**     err)
{
  GError* error = NULL;
  GConfEntry *entry = NULL;
  gboolean is_writable;

  g_return_val_if_fail (key != NULL, FALSE);
  g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

  if (gconf_client_lookup (client, key, &entry))
    {
      if (!entry)
        return FALSE;

      trace ("CACHED: Checking whether key '%s' is writable", key);
      return gconf_entry_get_is_writable (entry);
    }

  trace ("REMOTE: Checking whether key '%s' is writable", key);

  entry = get (client, key, TRUE, &error);

  if (entry == NULL && error != NULL)
    handle_error (client, error, err);
  else
    g_assert (error == NULL);

  if (entry == NULL)
    is_writable = FALSE;
  else
    is_writable = gconf_entry_get_is_writable (entry);

  if (entry)
    gconf_entry_free (entry);

  return is_writable;
}
