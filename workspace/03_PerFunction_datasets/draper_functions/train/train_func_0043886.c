treeview_key_press (GtkWidget           *treeview,
		    GdkEventKey         *event,
		    GladeEditorProperty *eprop)
{


  if (event->keyval == GDK_KEY_Delete)
    {
      GladeEPropStringList *eprop_string_list = GLADE_EPROP_STRING_LIST (eprop);
      GtkTreeSelection *selection;
      GtkTreeIter iter;
      GList *selected_rows, *l;

      selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));

      if ((selected_rows =
	   gtk_tree_selection_get_selected_rows (selection, NULL)) != NULL)
	{
	  for (l = selected_rows; l; l = l->next)
	    {
	      GtkTreePath *path = l->data;

	      if (gtk_tree_model_get_iter (eprop_string_list->model, &iter, path))
		gtk_list_store_remove (GTK_LIST_STORE (eprop_string_list->model), &iter);
	    }

	  g_list_foreach (selected_rows, (GFunc)gtk_tree_path_free, NULL);
	  g_list_free (selected_rows);
	}
      return TRUE;
    }

  return FALSE;
}
