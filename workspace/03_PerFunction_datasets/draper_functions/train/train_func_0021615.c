newbarbut_event(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED gpointer data) {
  if (animmode) return FALSE;


  netmode = 0;
  gtk_widget_hide(mainwin);
  gtk_widget_show(dialogwin);
  return FALSE;
}
