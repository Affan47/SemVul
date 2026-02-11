update_map_canvas_scrollbars(void)
{
  int scroll_x, scroll_y;

  get_mapview_scroll_pos(&scroll_x, &scroll_y);
  gtk_adjustment_set_value(map_hadj, scroll_x);
  gtk_adjustment_set_value(map_vadj, scroll_y);
  if (can_client_change_view()) {
    gtk_widget_queue_draw(overview_canvas);
  }
}
