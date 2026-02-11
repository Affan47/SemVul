addInitScript(const gchar *file, gboolean immediate, GtkWindow *parent)
{
  GtkTreeIter iter;
  gchar *path, *name;

  if (!g_file_test(file, G_FILE_TEST_IS_REGULAR))
    {
      if (parent)
        visu_ui_raiseWarning(_("Choose a Python script"),
                             _("Not a regular file."), parent);
      return;
    }

  path = tool_path_normalize(file);
  name = g_path_get_basename(file);
  gtk_list_store_append(initScripts, &iter);
  gtk_list_store_set(initScripts, &iter, SCRIPT_PATH, path, SCRIPT_LABEL, name, -1);
  g_free(name);

  if (immediate)
    {
      loadScript((gpointer)path);
      g_free(path);
    }
  else
    g_idle_add_full(G_PRIORITY_LOW, loadScript, (gpointer)path, g_free);
}
