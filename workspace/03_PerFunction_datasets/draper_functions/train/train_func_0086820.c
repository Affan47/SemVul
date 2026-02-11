tp_g_hash_table_update (GHashTable *target,
                        GHashTable *source,
                        GBoxedCopyFunc key_dup,
                        GBoxedCopyFunc value_dup)
{
  struct _tp_g_hash_table_update data = { target, key_dup,
      value_dup };

  g_return_if_fail (target != NULL);
  g_return_if_fail (source != NULL);
  g_return_if_fail (target != source);

  g_hash_table_foreach (source, _tp_g_hash_table_update_helper, &data);
}
