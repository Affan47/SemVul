connection_list_event(GtkWidget *widget,
                                      GdkEventButton *event,
                                      gpointer data)
{
  GtkTreeView *tree = GTK_TREE_VIEW(widget);
  GtkTreePath *path = NULL;
  GtkTreeSelection *selection = gtk_tree_view_get_selection(tree);
  gboolean ret = FALSE;

  if ((1 != event->button && 3 != event->button)
      || GDK_BUTTON_PRESS != event->type
      || !gtk_tree_view_get_path_at_pos(tree,
                                        event->x, event->y,
                                        &path, NULL, NULL, NULL)) {
    return FALSE;
  }

  if (1 == event->button) {
    if (gtk_tree_selection_path_is_selected(selection, path)) {

      g_idle_add(delayed_unselect_path, path);
      return FALSE;
    }
  } else if (3 == event->button) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree);
    GtkTreeIter iter;
    GtkWidget *menu;
    int player_no, conn_id;
    struct player *pplayer;
    struct connection *pconn;

    if (!gtk_tree_selection_path_is_selected(selection, path)) {
      gtk_tree_selection_select_path(selection, path);
    }
    gtk_tree_model_get_iter(model, &iter, path);

    gtk_tree_model_get(model, &iter, CL_COL_PLAYER_NUMBER, &player_no, -1);
    pplayer = player_by_number(player_no);

    gtk_tree_model_get(model, &iter, CL_COL_CONN_ID, &conn_id, -1);
    pconn = conn_by_number(conn_id);

    menu = create_conn_menu(pplayer, pconn);
    gtk_menu_popup(GTK_MENU(menu), NULL, NULL,
                   NULL, NULL, event->button, event->time);
    ret = TRUE;
  }

  gtk_tree_path_free(path);
  return ret;
}
