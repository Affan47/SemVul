o_select_box_start(GSCHEM_TOPLEVEL *w_current, int w_x, int w_y)
{
  int diff_x, diff_y;

  diff_x = abs(w_current->first_wx - w_x);
  diff_y = abs(w_current->first_wy - w_y);


  if (SCREENabs (w_current, max(diff_x, diff_y)) < 10) {
    return FALSE;
  }

  w_current->second_wx = w_x;
  w_current->second_wy = w_y;
  return TRUE;
}
