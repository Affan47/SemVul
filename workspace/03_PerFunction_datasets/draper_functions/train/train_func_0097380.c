get_list (DBusHashTable *hash,
          unsigned long  key)
{
  DBusList **list;

  list = _dbus_hash_table_lookup_uintptr (hash, key);

  if (list == NULL)
    {
      list = dbus_new0 (DBusList*, 1);
      if (list == NULL)
        return NULL;

      if (!_dbus_hash_table_insert_uintptr (hash, key, list))
        {
          dbus_free (list);
          return NULL;
        }
    }

  return list;
}
