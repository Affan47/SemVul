tp_intset_is_equal (const TpIntset *left,
    const TpIntset *right)
{
  gpointer key, value;
  GHashTableIter iter;

  g_return_val_if_fail (left != NULL, FALSE);
  g_return_val_if_fail (right != NULL, FALSE);

  if (g_hash_table_size (left->table) != g_hash_table_size (right->table))
    return FALSE;

  g_hash_table_iter_init (&iter, (GHashTable *) left->table);

  while (g_hash_table_iter_next (&iter, &key, &value))
    {
      if (g_hash_table_lookup (right->table, key) != value)
        {
          return FALSE;
        }
    }

  return TRUE;
}
