maptoggle_cb (GtkWidget * widget, guint datum)
{
  displaymap_map = !displaymap_map;
  if (displaymap_map)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (maptogglebt), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (maptogglebt), FALSE);
  current.needtosave = TRUE;
  return TRUE;
}
