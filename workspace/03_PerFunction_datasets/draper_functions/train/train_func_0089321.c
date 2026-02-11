activate_cb (GtkWidget *w, gpointer cb)
{
  char *text = gtk_combo_box_get_active_text (cb);
  if (text)
  {
    GtkTreeModel *tree = gtk_combo_box_get_model (cb);
    gint textcol = gtk_combo_box_entry_get_text_column (cb);
    GtkTreeIter iter;
    gboolean found = FALSE;
    if (gtk_tree_model_get_iter_first (tree, &iter))
    {
      do
      {
	GValue v = {};
	gtk_tree_model_get_value (tree, &iter, textcol, &v);
	const char *str = g_value_peek_pointer (&v);
	if (*str == *text && !strcmp (str, text))
	  found = TRUE;
	g_value_unset (&v);
      }
      while (!found && gtk_tree_model_iter_next (tree, &iter));
    }
    if (!found)
      gtk_combo_box_prepend_text (cb, text);

    history_activate_t fn =
      (history_activate_t) g_object_get_data (G_OBJECT (cb), "activate-fn");
    fn (cb, text);

    free (text);
  }
  free (eval_text);
  eval_text = NULL;
}
