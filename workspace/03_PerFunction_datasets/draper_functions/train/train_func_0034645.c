gnac_prefs_button_press_event_cb(GtkWidget      *widget,
                                 GdkEventButton *event,
                                 gpointer        user_data)
{
  if (!gnac_ui_utils_event_is_left_click(event)) return FALSE;

  GtkWidget *child = gtk_bin_get_child(GTK_BIN(user_data));
  GType widget_type = G_OBJECT_TYPE(widget);

  if (widget_type == GTK_TYPE_COMBO_BOX) {
    gnac_prefs_select_custom_pattern(GTK_COMBO_BOX(widget));
  } else if (widget_type == GTK_TYPE_RADIO_BUTTON) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
  }

  gtk_event_box_set_above_child(GTK_EVENT_BOX(user_data), FALSE);
  gtk_widget_set_sensitive(child, TRUE);
  gtk_widget_grab_focus(child);

  return TRUE;
}
