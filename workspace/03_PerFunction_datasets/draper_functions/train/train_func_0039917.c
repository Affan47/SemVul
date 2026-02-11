o_grips_end_box(GSCHEM_TOPLEVEL *w_current, OBJECT *o_current,
                            int whichone)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  int box_width, box_height;

  box_width  = GET_BOX_WIDTH (w_current);
  box_height = GET_BOX_HEIGHT(w_current);


  if ((box_width == 0) || (box_height == 0)) {
    o_box_invalidate_rubber (w_current);
    o_invalidate (w_current, o_current);
    return;
  }

  o_box_modify(toplevel, o_current, w_current->second_wx, w_current->second_wy, whichone);
}
