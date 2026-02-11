tp_handle_set_to_identifier_map (
    TpHandleSet *self)
{


  GHashTable *map = g_hash_table_new (NULL, NULL);
  TpIntsetFastIter iter;
  TpHandle handle;

  g_return_val_if_fail (self != NULL, map);

  tp_intset_fast_iter_init (&iter, self->intset);
  while (tp_intset_fast_iter_next (&iter, &handle))
    {
      if (handle == 0 || !tp_handle_is_valid (self->repo, handle, NULL))
        {
          WARNING ("handle set %p contains invalid handle #%u", self, handle);
        }
      else
        {
          g_hash_table_insert (map, GUINT_TO_POINTER (handle),
              (gchar *) tp_handle_inspect (self->repo, handle));
        }
    }

  return map;
}
