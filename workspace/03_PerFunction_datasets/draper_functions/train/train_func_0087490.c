gvdb_table_check_name (GvdbTable             *file,
                       struct gvdb_hash_item *item,
                       const gchar           *key,
                       guint                  key_length)
{
  const gchar *this_key;
  gsize this_size;
  guint32 parent;

  this_key = gvdb_table_item_get_key (file, item, &this_size);

  if G_UNLIKELY (this_key == NULL || this_size > key_length)
    return FALSE;

  key_length -= this_size;

  if G_UNLIKELY (memcmp (this_key, key + key_length, this_size) != 0)
    return FALSE;

  parent = guint32_from_le (item->parent);
  if (key_length == 0 && parent == 0xffffffffu)
    return TRUE;

  if G_LIKELY (parent < file->n_hash_items && this_size > 0)
    return gvdb_table_check_name (file,
                                   &file->hash_items[parent],
                                   key, key_length);

  return FALSE;
}
