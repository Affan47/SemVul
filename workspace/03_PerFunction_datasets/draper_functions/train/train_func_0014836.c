dialogwin_delete_event(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED GdkEvent *event, G_GNUC_UNUSED gpointer data) {
  if (netmode) return FALSE;
  if (gamestatus == 0) {
    gtk_main_quit();
    return FALSE;
  }
  gtk_widget_hide(dialogwin);
  gtk_widget_show(mainwin);
  return TRUE;
}
