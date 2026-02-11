request_toggle_city_full_bar(void)
{
  if (!can_client_change_view()) {
    return;
  }

  draw_full_citybar ^= 1;
  update_map_canvas_visible();
}
