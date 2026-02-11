on_status_bar_check_activate (GtkCheckMenuItem * menuitem, gpointer user_data)
{
  if (menuitem->active)
    gtk_widget_show (GTK_WIDGET(appdata.statusbar));
  else
    gtk_widget_hide (GTK_WIDGET(appdata.statusbar));
}
