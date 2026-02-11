button_cb (GtkWidget *widget, GdkEventButton *ev, gpointer data)
{
  switch (ev->button)
  {
  case 1:
    gtk_menu_popup (GTK_MENU (tray_menu), NULL, NULL, NULL, NULL,
		    ev->button, ev->time);
    break;
  case 2:
    if (GTK_WIDGET_MAPPED (app))
      app_hide ();
    else
      app_show ();
    break;
  case 3:
    gtk_menu_popup (GTK_MENU (popup_menu), NULL, NULL, NULL, NULL,
		    ev->button, ev->time);
    break;
  }

  return TRUE;
}
