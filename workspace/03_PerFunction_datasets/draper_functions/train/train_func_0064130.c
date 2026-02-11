go_option_menu_show_all (GtkWidget *widget)
{
  GtkContainer *container;
  GOOptionMenu *option_menu;

  g_return_if_fail (GO_IS_OPTION_MENU (widget));
  container = GTK_CONTAINER (widget);
  option_menu = GO_OPTION_MENU (widget);

  gtk_widget_show (widget);
  gtk_container_foreach (container, (GtkCallback) gtk_widget_show_all, NULL);
  if (option_menu->menu)
    gtk_widget_show_all (option_menu->menu);
  if (option_menu->menu_item)
    gtk_widget_show_all (option_menu->menu_item);
  if (option_menu->last_signaled_menu_item)
    gtk_widget_show_all (option_menu->last_signaled_menu_item);
  if (option_menu->select_menu)
	  gtk_widget_show_all (option_menu->select_menu);
}
