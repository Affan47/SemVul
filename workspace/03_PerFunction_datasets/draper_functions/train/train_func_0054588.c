resize_minimap(void)
{

  overview_w = overview.width;
  overview_h = overview.height;
  overview_start_x = (overview_w - overview.width)/2;
  overview_start_y = (overview_h - overview.height)/2;

  if (C_S_RUNNING == client_state()) {
    popdown_minimap_window();
    popup_minimap_window();
    refresh_overview();
    menus_update();
  }

  return 0;
}
