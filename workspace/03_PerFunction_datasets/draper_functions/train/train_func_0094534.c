roi_width_cb(GtkWidget * widget, gpointer data) {

  ui_study_t * ui_study = data;
  gint new_roi_width;

  g_return_if_fail(ui_study->study != NULL);

  new_roi_width = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
  amitk_preferences_set_canvas_roi_width(ui_study->preferences, new_roi_width);
  update_roi_sample_item(ui_study);

  return;
}
