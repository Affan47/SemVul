o_net_start_magnetic(GSCHEM_TOPLEVEL *w_current, int w_x, int w_y)
{
  o_net_invalidate_rubber (w_current);

  if (w_current->CONTROLKEY) {
    w_current->magnetic_wx = w_x;
    w_current->magnetic_wy = w_y;
  }
  else {
    o_net_find_magnetic(w_current, w_x, w_y);
  }

  o_net_invalidate_rubber (w_current);
  w_current->rubber_visible = 1;
  w_current->inside_action = 1;
}
