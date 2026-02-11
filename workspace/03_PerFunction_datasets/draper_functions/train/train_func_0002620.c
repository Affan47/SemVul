bytes_multi_table_lookup_ref_one (GHashTable *table,
                                  GBytes     *key)
{
  GPtrArray *multi;

  multi = g_hash_table_lookup (table, key);
  if (multi == NULL)
    return NULL;

  g_assert (multi->len > 0);
  return g_bytes_ref (multi->pdata[0]);
}
