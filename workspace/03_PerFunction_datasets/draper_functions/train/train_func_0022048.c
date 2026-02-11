setEnabled() {
  gint enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_enable));
  if (enabled) {
    _op._enabled = true;
    gtk_widget_set_sensitive(_controls, TRUE);
    if (_op._relative) {
      gtk_widget_set_sensitive(_relativeFrame, TRUE);
      gtk_widget_set_sensitive(_absoluteFrame, FALSE);
    } else {
      gtk_widget_set_sensitive(_relativeFrame, FALSE);
      gtk_widget_set_sensitive(_absoluteFrame, TRUE);
    }
  } else {
    _op._enabled = false;
    gtk_widget_set_sensitive(_controls, FALSE);
    gtk_widget_set_sensitive(_relativeFrame, FALSE);
    gtk_widget_set_sensitive(_absoluteFrame, FALSE);
  }
}
