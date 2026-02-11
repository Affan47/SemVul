setBusy(bool busy) {
  if (busy) {
    gtk_widget_set_sensitive(_test, FALSE);
    gtk_widget_set_sensitive(_start, FALSE);
    gtk_widget_set_sensitive(_cancel, TRUE);
  } else {
    gtk_widget_set_sensitive(_test, TRUE);
    gtk_widget_set_sensitive(_start, TRUE);
    gtk_widget_set_sensitive(_cancel, FALSE);
  }
}
