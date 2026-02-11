get_profile_selected(metro_t* metro,
                                        int n _U_, char** option_name _U_)
{
  static gchar selected[16];
  selected[0] = '1';
  selected[1] = 0;
  if (metro) {
    GtkListStore* store;
    if ((store =
          GTK_LIST_STORE(gtk_tree_view_get_model(metro->profiles_tree))))
    {
      GtkTreeSelection* selection =
        gtk_tree_view_get_selection(metro->profiles_tree);
      GtkTreeIter iter;
      int n = 1;
      if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter)) {
        gboolean valid = TRUE;

        while (valid && !gtk_tree_selection_iter_is_selected(selection, &iter)) {
	  valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
	  n++;
	}
	if (valid) {
	  g_snprintf(selected, 16, "%d", n);
	}
      } else if (debug)
          g_print("get_profile_selected(): No items.\n");
    } else g_print("get_profile_selected(): No tree model available.\n");
  }
  return selected;
}
