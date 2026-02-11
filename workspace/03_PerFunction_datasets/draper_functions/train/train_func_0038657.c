dict_entry_remove (struct hash_table_s * table, const char * key)
{
  struct dict_entry * item;
  item = dict_entry_get (table, key);
  if (item) {
    hash_delete (table, item);
    free_dict_entry (item);
  }
}
