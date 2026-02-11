close_cb(GtkAction * action, gpointer data) {

  ui_series_t * ui_series = data;
  GtkWindow * window = ui_series->window;
  gboolean return_val;


  g_signal_emit_by_name(G_OBJECT(window), "delete_event", NULL, &return_val);
  if (!return_val) gtk_widget_destroy(GTK_WIDGET(window));

  return;
}
