add_meta_entry (const gchar *l, int info)
{
  GtkTreeIter  iter;
  const char *str = xine_get_meta_info (stream, info);
  if (!str)
    return;

  gtk_list_store_append (meta_store, &iter);
  gtk_list_store_set (meta_store, &iter, 0, l, 1,
		      g_utf8_normalize (str, -1, G_NORMALIZE_DEFAULT), -1);
}
