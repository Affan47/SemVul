tp_asv_take_bytes (GHashTable *asv,
                   const gchar *key,
                   GArray *value)
{
  g_return_if_fail (asv != NULL);
  g_return_if_fail (key != NULL);
  g_return_if_fail (value != NULL);

  g_hash_table_insert (asv, (char *) key,
      tp_g_value_slice_new_take_bytes (value));
}
