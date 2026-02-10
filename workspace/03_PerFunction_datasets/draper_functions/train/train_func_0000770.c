tree_view_button_press_event (GtkTreeView        *view,
                              GdkEventButton     *event,
                              GgdDoctypeSelector *selector)
{
  gboolean handled = FALSE;


  if (event->button == 3 && event->type == GDK_BUTTON_PRESS) {
    GtkTreePath *path;


    if (gtk_tree_view_get_path_at_pos (view, (gint)event->x, (gint)event->y,
                                       &path, NULL, NULL, NULL)) {
      gtk_tree_selection_select_path (gtk_tree_view_get_selection (view), path);
      gtk_tree_view_scroll_to_cell (view, path, NULL, FALSE, 0.0, 0.0);
      gtk_tree_path_free (path);
    }
    do_popup_menu (selector, event);
    handled = TRUE;
  }

  return handled;
}
