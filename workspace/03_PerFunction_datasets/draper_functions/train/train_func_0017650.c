inf_gtk_browser_view_popup_menu_position_func(GtkMenu* menu,
                                              gint* x,
                                              gint* y,
                                              gboolean* push_in,
                                              gpointer user_data)
{
  InfGtkBrowserView* view;
  InfGtkBrowserViewPrivate* priv;
  GdkWindow* bin_window;
  GdkScreen* screen;
  GtkRequisition menu_req;
  GdkRectangle monitor;
  gint monitor_num;
  gint orig_x;
  gint orig_y;
  gint height;

  GtkTreeSelection* selection;
  GtkTreeModel* model;
  GtkTreeIter selected_iter;
  GtkTreePath* selected_path;
  GdkRectangle cell_area;

  view = INF_GTK_BROWSER_VIEW(user_data);
  priv = INF_GTK_BROWSER_VIEW_PRIVATE(view);


  bin_window = gtk_tree_view_get_bin_window(GTK_TREE_VIEW(view));
  gdk_window_get_origin(bin_window, &orig_x, &orig_y);

  screen = gtk_widget_get_screen(GTK_WIDGET(view));
  monitor_num = gdk_screen_get_monitor_at_window(screen, bin_window);
  if(monitor_num < 0) monitor_num = 0;
  gtk_menu_set_monitor(menu, monitor_num);

  gdk_screen_get_monitor_geometry(screen, monitor_num, &monitor);
  gtk_widget_size_request(GTK_WIDGET(menu), &menu_req);

#if GTK_CHECK_VERSION(2, 91, 0)
      height = gdk_window_get_height(bin_window);
#else
      gdk_drawable_get_size(GDK_DRAWABLE(bin_window), NULL, &height);
#endif

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
  gtk_tree_selection_get_selected(selection, &model, &selected_iter);
  selected_path = gtk_tree_model_get_path(model, &selected_iter);
  gtk_tree_view_get_cell_area(
    GTK_TREE_VIEW(view),
    selected_path,
    priv->column,
    &cell_area
  );
  gtk_tree_path_free(selected_path);

  g_assert(cell_area.height > 0);

  if(gtk_widget_get_direction(GTK_WIDGET(view)) == GTK_TEXT_DIR_LTR)
    *x = orig_x + cell_area.x + cell_area.width - menu_req.width;
  else
    *x = orig_x + cell_area.x;

  *y = orig_y + cell_area.y + cell_area.height;


  if(*y < orig_y)
    *y = orig_y;
  if(*y > orig_y + height)
    *y = orig_y + height;


  if(*y + menu_req.height > monitor.y + monitor.height)
    *y = monitor.y + monitor.height - menu_req.height;
  if(*y < monitor.y)
    *y = monitor.y;

  *push_in = FALSE;
}
