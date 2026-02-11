sw_set_filter (SwSet           *set_in,
               SwSetFilterFunc  func,
               gpointer         user_data)
{
  GHashTableIter iter;
  gpointer object;
  SwSet *set = NULL;

  g_return_val_if_fail (set_in, NULL);
  g_return_val_if_fail (func, NULL);

  set = sw_set_new_full (set_in->hash_func,
                             set_in->equal_func);

  g_hash_table_iter_init (&iter, set_in->hash);
  while (g_hash_table_iter_next (&iter, &object, NULL)) {

    if (func (set_in, object, user_data))
    {
      add (set, object);
    }
  }

  return set;
}
