dconf_gvdb_utils_add_key (const gchar *path,
                          GVariant    *value,
                          gpointer     user_data)
{
  GHashTable *gvdb = user_data;
  GvdbItem *item;

  g_assert (g_hash_table_lookup (gvdb, path) == NULL);
  item = gvdb_hash_table_insert (gvdb, path);
  gvdb_item_set_parent (item, dconf_gvdb_utils_get_parent (gvdb, path));
  gvdb_item_set_value (item, value);

  return TRUE;
}
