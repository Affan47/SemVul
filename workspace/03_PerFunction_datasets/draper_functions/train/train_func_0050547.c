cb_button_release (GtkWidget      * widget,
		   GdkEventButton * event,
		   gpointer         data)
{
  BaconVolumeButton *button = BACON_VOLUME_BUTTON (data);

  if (button->click_id != 0) {
    g_source_remove (button->click_id);
    button->click_id = 0;
  }

  return TRUE;
}
