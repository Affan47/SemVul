set_sensitive_timer (GtkWidget *widget)
{
  set_sensitive (widget, !GTK_WIDGET_IS_SENSITIVE (widget));
  return FALSE;
}
