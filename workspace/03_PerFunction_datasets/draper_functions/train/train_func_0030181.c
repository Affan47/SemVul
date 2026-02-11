chmod_action (GtkWidget * widget, gint response, gpointer wdata)
{
  switch (response)
    {
      case GTK_RESPONSE_OK:
        dochmod (widget, wdata);

      default:
        gtk_widget_destroy (widget);
    }
}
