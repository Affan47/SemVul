gegl_list_operations (guint *n_operations_p)
{
  gchar **pasp = NULL;
  gint    n_operations;
  gint    i;
  GSList *iter;
  gint    pasp_size = 0;
  gint    pasp_pos;

  if (!operations_list)
    {
      gegl_operation_gtype_from_name ("");

      G_LOCK (gtype_hash);
      g_hash_table_foreach (gtype_hash, addop, NULL);
      G_UNLOCK (gtype_hash);

      operations_list = g_slist_sort (operations_list, (GCompareFunc) strcmp);
    }

  n_operations = g_slist_length (operations_list);
  pasp_size   += (n_operations + 1) * sizeof (gchar *);
  for (iter = operations_list; iter != NULL; iter = g_slist_next (iter))
    {
      const gchar *name = iter->data;
      pasp_size += strlen (name) + 1;
    }
  pasp     = g_malloc (pasp_size);
  pasp_pos = (n_operations + 1) * sizeof (gchar *);
  for (iter = operations_list, i = 0; iter != NULL; iter = g_slist_next (iter), i++)
    {
      const gchar *name = iter->data;
      pasp[i] = ((gchar *) pasp) + pasp_pos;
      strcpy (pasp[i], name);
      pasp_pos += strlen (name) + 1;
    }
  pasp[i] = NULL;
  if (n_operations_p)
    *n_operations_p = n_operations;
  return pasp;
}
