blocked_changed_item_new (TpConnection *conn,
    GHashTable *added,
    GHashTable *removed,
    GSimpleAsyncResult *result)
{
  BlockedChangedItem *item = g_slice_new0 (BlockedChangedItem);

  item->added = g_hash_table_ref (added);

  if (removed != NULL)
    item->removed = g_hash_table_ref (removed);
  else
    item->removed = g_hash_table_new (NULL, NULL);

  item->added_contacts = g_ptr_array_new_with_free_func (g_object_unref);
  item->removed_contacts = g_ptr_array_new_with_free_func (g_object_unref);

  if (result != NULL)
    item->result = g_object_ref (result);

  return item;
}
