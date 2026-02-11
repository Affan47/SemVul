anthy_input_beginning_of_line(struct anthy_input_context* ictx)
{
  switch (ictx->state) {
  case ANTHY_INPUT_ST_OFF:
    break;
  case ANTHY_INPUT_ST_NONE:
    break;
  case ANTHY_INPUT_ST_EDIT:
    cmd_move_to_bol(ictx);
    break;
  case ANTHY_INPUT_ST_CONV:
    cmd_move_to_bol_seg(ictx);
    break;
  case ANTHY_INPUT_ST_CSEG:
    break;
  }
}
