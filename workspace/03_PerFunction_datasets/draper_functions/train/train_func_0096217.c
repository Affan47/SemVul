scenario_callback(void)
{
  GtkTreeIter it;
  char *filename;

  if (!gtk_tree_selection_get_selected(scenario_selection, NULL, &it)) {
    return;
  }

  gtk_tree_model_get(GTK_TREE_MODEL(scenario_store), &it, 1, &filename, -1);
  load_filename(filename);
}
