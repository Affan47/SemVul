on_button_pressed(GtkWidget * treeview, GdkEventButton * event, gpointer userdata)
{

  if (event->type == GDK_BUTTON_PRESS && event->button == 3)
  {

    {
      GtkTreeSelection *selection;

      selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));


      if (gtk_tree_selection_count_selected_rows(selection) <= 1)
      {
        GtkTreePath *path;


        if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint)event->x, (gint)event->y, &path, NULL, NULL, NULL))
        {
          gtk_tree_selection_unselect_all(selection);
          gtk_tree_selection_select_path(selection, path);
          gtk_tree_path_free(path);
        }
      }
    }

    popup_menu(treeview, event);

    return TRUE;
  }

  return FALSE;
}
