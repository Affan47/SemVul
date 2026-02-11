exportParameters(GString *data, VisuData *dataObj _U_, VisuGlView *view _U_)
{
  gboolean valid;
  GtkTreeIter iter;
  gchar *file;

  g_string_append_printf(data, "# %s\n", DESC_PARAMETER_INIT_SCRIPTS);
      g_string_append_printf(data, "%s[python]: ", FLAG_PARAMETER_INIT_SCRIPTS);
  for (valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(initScripts), &iter);
       valid; valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(initScripts), &iter))
    {
      gtk_tree_model_get(GTK_TREE_MODEL(initScripts), &iter, SCRIPT_PATH, &file, -1);
      g_string_append_printf(data, "%s:", file);
      g_free(file);
    }
  g_string_append_printf(data, "\n\n");
}
