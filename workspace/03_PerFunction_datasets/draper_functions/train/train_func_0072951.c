city_dialog_map_recenter(GtkWidget *map_canvas_sw) {
  GtkAdjustment *adjust = NULL;
  gdouble value;

  fc_assert_ret(map_canvas_sw != NULL);

  adjust = gtk_scrolled_window_get_hadjustment(
    GTK_SCROLLED_WINDOW(map_canvas_sw));
  value = (gtk_adjustment_get_lower(adjust)
    + gtk_adjustment_get_upper(adjust)
    - gtk_adjustment_get_page_size(adjust)) / 2;
  gtk_adjustment_set_value(adjust, value);
  gtk_adjustment_value_changed(adjust);

  adjust = gtk_scrolled_window_get_vadjustment(
    GTK_SCROLLED_WINDOW(map_canvas_sw));
  value = (gtk_adjustment_get_lower(adjust)
    + gtk_adjustment_get_upper(adjust)
    - gtk_adjustment_get_page_size(adjust)) / 2;
  gtk_adjustment_set_value(adjust, value);
  gtk_adjustment_value_changed(adjust);
}
