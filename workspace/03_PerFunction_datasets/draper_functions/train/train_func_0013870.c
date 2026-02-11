gvdb_table_item_get_key (GvdbTable                   *file,
                         const struct gvdb_hash_item *item,
                         gsize                       *size)
{
  guint32 start, end;

  start = guint32_from_le (item->key_start);
  *size = guint16_from_le (item->key_size);
  end = start + *size;

  if G_UNLIKELY (start > end || end > file->size)
    return NULL;

  return file->data + start;
}
