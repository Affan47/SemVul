game_speed_cb (GtkWidget * widget, gpointer data)
{
  if (!pref_dialog)
    return;

  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) {
    gnibbles_properties_set_speed (GPOINTER_TO_INT (data));
  }
}
