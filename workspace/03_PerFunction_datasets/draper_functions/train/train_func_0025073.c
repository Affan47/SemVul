polkit_details_insert (PolkitDetails *details,
                       const gchar   *key,
                       const gchar   *value)
{
  g_return_if_fail (POLKIT_IS_DETAILS (details));
  g_return_if_fail (key != NULL);
  if (details->hash == NULL)
    details->hash = g_hash_table_new_full (g_str_hash,
                                           g_str_equal,
                                           g_free,
                                           g_free);
  g_hash_table_insert (details->hash, g_strdup (key), g_strdup (value));
}
