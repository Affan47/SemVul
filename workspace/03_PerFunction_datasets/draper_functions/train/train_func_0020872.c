gen_items (GtkUIManager *ui, const char *path, GtkTreeIter *iter,
		      guint merge, int count)
{
  do
  {
    if (peek_title (iter))
    {
      char *name = g_strdup_printf ("_mediamark_%d", count++);
      play_item_t *item = peek_play_item (iter);
      if (item)
	gtk_ui_manager_add_ui (ui, merge, path, name, name,
			       GTK_UI_MANAGER_MENUITEM, FALSE);
      else
      {
	GtkTreeIter children;
	gtk_ui_manager_add_ui (ui, merge, path, name, name,
			       GTK_UI_MANAGER_MENU, FALSE);
	if (gtk_tree_model_iter_children (mm_model, &children, iter))
	{
	  char *newpath = g_strdup_printf ("%s/%s", path, name);
	  count = gen_items (ui, newpath, &children, merge, count);
	  free (newpath);
	}
      }
    }
  } while (gtk_tree_model_iter_next (mm_model, iter));

  return count;
}
