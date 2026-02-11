visu_data_getFilesAsLabel(const VisuData *data)
{
  GList *lst;
  GString *str;
  gchar *s;

  g_return_val_if_fail(VISU_IS_DATA(data), (gchar*)0);

  if (!data->priv->files)
    return (gchar*)0;

  DBG_fprintf(stderr, "Visu Data: retrieve all filenames"
	      " from the VisuData %p.\n", (gpointer)data);
  str = g_string_new("");
  for (lst = data->priv->files->next; lst; lst = g_list_next(lst))
    {
      s = g_path_get_basename(((struct FileDescription_struct*)lst->data)->name);
      g_string_append_printf(str, "\302\240\342\200\224 %s", s);
      g_free(s);
    }
  s = g_path_get_basename(((struct FileDescription_struct*)data->priv->files->data)->name);
  g_string_prepend(str, s);
  g_free(s);
  DBG_fprintf(stderr, " | '%s'\n", str->str);
  return g_string_free(str, FALSE);
}
