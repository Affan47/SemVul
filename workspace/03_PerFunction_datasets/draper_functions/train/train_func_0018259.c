button_press_event_cb (GtkWidget *widget,
                       GdkEventButton *event,
                       EggEditableToolbar *etoolbar)
{
  if (event->button == 3 && etoolbar->priv->popup_path != NULL)
    {
      GtkMenu *menu;

      egg_editable_toolbar_set_selected (etoolbar, widget);
      g_object_notify (G_OBJECT (etoolbar), "selected");

      menu = GTK_MENU (gtk_ui_manager_get_widget (etoolbar->priv->manager,
						  etoolbar->priv->popup_path));
      g_return_val_if_fail (menu != NULL, FALSE);
      gtk_menu_popup (menu, NULL, NULL, NULL, NULL, event->button, event->time);
      g_signal_connect_object (menu, "selection-done",
			       G_CALLBACK (popup_context_deactivate),
			       etoolbar, 0);

      return TRUE;
    }

  return FALSE;
}
