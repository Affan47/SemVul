o_line_motion (GSCHEM_TOPLEVEL *w_current, int w_x, int w_y)
{
  int diff_x, diff_y;

  g_assert( w_current->inside_action != 0 );

  if (w_current->rubber_visible)
    o_line_invalidate_rubber (w_current);


  w_current->second_wx = w_x;
  w_current->second_wy = w_y;


  if (w_current->CONTROLKEY) {
    diff_x = abs(w_current->second_wx - w_current->first_wx);
    diff_y = abs(w_current->second_wy - w_current->first_wy);

    if (diff_x >= diff_y) {
      w_current->second_wy = w_current->first_wy;
    } else {
      w_current->second_wx = w_current->first_wx;
    }
  }

  o_line_invalidate_rubber (w_current);
  w_current->rubber_visible = 1;
}
