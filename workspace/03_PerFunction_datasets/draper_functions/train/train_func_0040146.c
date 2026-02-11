interactive_dialog_key_press_cb (GtkWidget *widget,
                                 GdkEventKey *event,
                                 gpointer user_data)
{
  if (event->keyval == GDK_KEY_F1)
    {
      screenshot_display_help (GTK_WINDOW (widget));
      return TRUE;
    }

  if (event->keyval == GDK_KEY_Escape)
    {
      gtk_widget_destroy (widget);
      return TRUE;
    }

  return FALSE;
}
