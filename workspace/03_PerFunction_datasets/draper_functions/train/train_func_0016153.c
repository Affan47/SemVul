blocked_changed_item_free (BlockedChangedItem *item)
{
  g_hash_table_unref (item->added);
  g_hash_table_unref (item->removed);
  g_ptr_array_unref (item->added_contacts);
  g_ptr_array_unref (item->removed_contacts);
  g_clear_object (&item->result);

  g_slice_free (BlockedChangedItem, item);
}
