Cursor_displace(short delta_x, short delta_y)
{
  short x=Input_new_mouse_X;
  short y=Input_new_mouse_Y;

  if(Main_magnifier_mode && Input_new_mouse_Y < Menu_Y && Input_new_mouse_X > Main_separator_position)
  {


    if (delta_x<0)
      Input_new_mouse_X = Max(Main_separator_position, x-Main_magnifier_factor);
    else if (delta_x>0)
      Input_new_mouse_X = Min(Screen_width-1, x+Main_magnifier_factor);
    if (delta_y<0)
      Input_new_mouse_Y = Max(0, y-Main_magnifier_factor);
    else if (delta_y>0)
      Input_new_mouse_Y = Min(Screen_height-1, y+Main_magnifier_factor);
  }
  else
  {
    if (delta_x<0)
      Input_new_mouse_X = Max(0, x+delta_x);
    else if (delta_x>0)
      Input_new_mouse_X = Min(Screen_width-1, x+delta_x);
    if (delta_y<0)
      Input_new_mouse_Y = Max(0, y+delta_y);
    else if (delta_y>0)
      Input_new_mouse_Y = Min(Screen_height-1, y+delta_y);
  }
  return Move_cursor_with_constraints();
}
