o_grips_start(GSCHEM_TOPLEVEL *w_current, int w_x, int w_y)
{
  OBJECT *object;
  int whichone;

  if (w_current->draw_grips == FALSE) {
    return(FALSE);
  }


  object = o_grips_search_world(w_current, w_x, w_y, &whichone);

  if (object == NULL)
    return FALSE;

  w_current->which_grip = whichone;
  w_current->which_object = object;


  object->dont_redraw = TRUE;
  o_invalidate (w_current, object);


  switch(object->type) {
    case(OBJ_ARC):

      o_grips_start_arc(w_current, object, w_x, w_y, whichone);
      return(TRUE);

    case(OBJ_BOX):

      o_grips_start_box(w_current, object, w_x, w_y, whichone);
      return(TRUE);

    case(OBJ_PATH):

      o_grips_start_path(w_current, object, w_x, w_y, whichone);
      return(TRUE);

    case(OBJ_PICTURE):

      o_grips_start_picture(w_current, object, w_x, w_y, whichone);
      return(TRUE);

    case(OBJ_CIRCLE):

      o_grips_start_circle(w_current, object, w_x, w_y, whichone);
      return(TRUE);

    case(OBJ_LINE):
    case(OBJ_NET):
    case(OBJ_PIN):
    case(OBJ_BUS):


      o_grips_start_line(w_current, object, w_x, w_y, whichone);
      return(TRUE);

    default:

      return(FALSE);
  }
  return(FALSE);
}
