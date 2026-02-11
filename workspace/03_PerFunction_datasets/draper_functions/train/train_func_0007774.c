o_grips_end_arc(GSCHEM_TOPLEVEL *w_current, OBJECT *o_current,
                            int whichone)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  int arg1, arg2;


  switch(whichone) {
    case ARC_RADIUS:

      arg1 = w_current->distance;

      arg2 = -1;
      break;

    case ARC_START_ANGLE:

      arg1 = w_current->second_wx;

      arg2 = -1;
      break;

    case ARC_END_ANGLE:

      arg1 = w_current->second_wy;

      arg2 = -1;
      break;

    default:
      return;
  }


  o_arc_modify(toplevel, o_current, arg1, arg2, whichone);
}
