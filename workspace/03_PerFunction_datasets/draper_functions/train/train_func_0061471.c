lint_row_activated (GtkTreeSelection *selection, gpointer data)
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *line;
  gchar *space;

  if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
    gtk_tree_model_get (model, &iter, 0, &line, -1);


    space = strrchr(line, ' ');
    space++;

      goto_line(space);

    g_free (line);
  }
}
