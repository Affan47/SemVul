option_menu_get_history (GtkOptionMenu *option_menu)
{
  GtkWidget *active_widget;

  g_return_val_if_fail (GTK_IS_OPTION_MENU (option_menu), -1);

  active_widget = gtk_menu_get_active (GTK_MENU (option_menu->menu));

  if (active_widget)
    return g_list_index (GTK_MENU_SHELL (option_menu->menu)->children,
			 active_widget);
  else
    return -1;
}
