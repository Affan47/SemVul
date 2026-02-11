sw_set_has (SwSet   *set,
            GObject *item)
{
  g_return_val_if_fail (set, FALSE);
  g_return_val_if_fail (G_IS_OBJECT (item), FALSE);

  return g_hash_table_lookup (set->hash, item) != NULL;
}
