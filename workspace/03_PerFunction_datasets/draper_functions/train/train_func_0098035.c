gnac_ui_file_chooser_key_press_event_cb(GtkWidget   *widget,
                                        GdkEventKey *event,
                                        gpointer     user_data)
{
  if (gnac_ui_utils_event_is_return_key(event)) {
    gnac_ui_file_chooser_response_cb(GTK_DIALOG(widget),
        GTK_RESPONSE_NONE, NULL);
    return TRUE;
  }
  return FALSE;
}
