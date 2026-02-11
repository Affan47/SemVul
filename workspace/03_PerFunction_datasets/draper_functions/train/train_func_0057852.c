tp_intset_copy (const TpIntset *orig)
{
  gpointer key, value;
  GHashTableIter iter;
  TpIntset *ret;

  g_return_val_if_fail (orig != NULL, NULL);

  ret = tp_intset_new ();

  g_hash_table_iter_init (&iter, (GHashTable *) orig->table);

  while (g_hash_table_iter_next (&iter, &key, &value))
    {
      intset_update_largest_ever (ret, key);
      g_hash_table_insert (ret->table, key, value);
    }

  return ret;
}
