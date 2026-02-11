gvdb_table_value_from_item (GvdbTable                   *table,
                            const struct gvdb_hash_item *item)
{
  GVariant *variant, *value;
  gconstpointer data;
  GBytes *bytes;
  gsize size;

  data = gvdb_table_dereference (table, &item->value.pointer, 8, &size);

  if G_UNLIKELY (data == NULL)
    return NULL;

  bytes = g_bytes_new_from_bytes (table->bytes, ((gchar *) data) - table->data, size);
  variant = g_variant_new_from_bytes (G_VARIANT_TYPE_VARIANT, bytes, table->trusted);
  value = g_variant_get_variant (variant);
  g_variant_unref (variant);
  g_bytes_unref (bytes);

  return value;
}
