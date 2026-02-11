op_erase_window(void)
{
  if(!allow_output)
    return;

#ifdef DEBUG_IO
  n_show_debug(E_OUTPUT, "erase_window", operand[0]);
  return;
#endif

  switch(operand[0]) {
  case neg(1):
    operand[0] = 0; op_split_window();
    current_window = lower_win;
  case neg(2):
  case UPPER_WINDOW:
    z_clear_window(upper_win);
    if(operand[0] == UPPER_WINDOW) break;
  case LOWER_WINDOW:
    z_clear_window(lower_win);
    break;
  }
}
