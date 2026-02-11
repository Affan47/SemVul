o_net_start(GSCHEM_TOPLEVEL *w_current, int w_x, int w_y)
{
  if (w_current->magnetic_wx != -1 && w_current->magnetic_wy != -1) {
    w_current->first_wx = w_current->magnetic_wx;
    w_current->first_wy = w_current->magnetic_wy;
  }
  else {
    w_current->first_wx = w_x;
    w_current->first_wy = w_y;
  }

  w_current->second_wx = w_current->third_wx = w_current->first_wx;
  w_current->second_wy = w_current->third_wy = w_current->first_wy;

  if (w_current->first_wx != snap_grid (w_current, w_current->first_wx)
      || w_current->first_wy != snap_grid (w_current, w_current->first_wy))
      s_log_message(_("Warning: Starting net at off grid coordinate\n"));

  if (w_current->net_direction_mode)
    o_net_guess_direction(w_current, w_current->first_wx, w_current->first_wy);
}
