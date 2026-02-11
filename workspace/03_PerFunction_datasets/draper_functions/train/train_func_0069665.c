scroll_mapview(enum direction8 gui_dir)
{
  int gui_x = mapview.gui_x0, gui_y = mapview.gui_y0;

  if (!can_client_change_view()) {
    return;
  }

  gui_x += DIR_DX[gui_dir] * mapview.width / 2;
  gui_y += DIR_DY[gui_dir] * mapview.height / 2;
  set_mapview_origin(gui_x, gui_y);
}
