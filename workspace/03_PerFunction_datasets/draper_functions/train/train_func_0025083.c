emerillon_sidebar_select_button_press_cb (GtkWidget *widget,
                                           GdkEventButton *event,
                                           gpointer user_data)
{
  EmerillonSidebar *sidebar = EMERILLON_SIDEBAR (user_data);

  if (event->button == 1)
    {
      gint preferred_width;
      gint width;

      GtkAllocation allocation;
      gtk_widget_get_allocation (widget, &allocation);
      width = allocation.width;

      gtk_widget_set_size_request (sidebar->priv->menu, -1, -1);
      gtk_widget_get_preferred_width(sidebar->priv->menu, NULL,
          &preferred_width);
      gtk_widget_set_size_request (sidebar->priv->menu,
          MAX (width, preferred_width), -1);

      gtk_widget_grab_focus (widget);

      gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

      gtk_menu_popup (GTK_MENU (sidebar->priv->menu),
          NULL, NULL, emerillon_sidebar_menu_position_under, widget,
          event->button, event->time);

      return TRUE;
    }

  return FALSE;
}
