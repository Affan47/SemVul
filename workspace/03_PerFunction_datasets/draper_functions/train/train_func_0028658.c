detach_canvas(struct graph_view * view_ptr)
{
  GtkWidget * child;

  child = gtk_bin_get_child(GTK_BIN(g_main_scrolledwin));
  if (child == view_ptr->canvas_widget)
  {
    gtk_container_remove(GTK_CONTAINER(g_main_scrolledwin), view_ptr->canvas_widget);
    g_current_view = NULL;
    gtk_widget_show(g_view_label);
    gtk_scrolled_window_add_with_viewport(g_main_scrolledwin, g_view_label);
  }
}
