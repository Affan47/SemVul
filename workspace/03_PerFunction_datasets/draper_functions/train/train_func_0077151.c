format_set (gint fmt, ggobid *gg) {
  GtkTreeSelection *sel = gtk_tree_view_get_selection (GTK_TREE_VIEW (gg->save.tree_view));

  gg->save.format = fmt;
  if (fmt == 0)
    gtk_tree_selection_set_mode (sel, GTK_SELECTION_MULTIPLE);
  else
    gtk_tree_selection_set_mode (sel, GTK_SELECTION_SINGLE);
}
