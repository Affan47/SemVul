Horizontal_XOR_line_zoom(short x_pos, short y_pos, short width)
{
  short real_x_pos=Main_X_zoom+(x_pos-Main_magnifier_offset_X)*Main_magnifier_factor;
  short real_y_pos=(y_pos-Main_magnifier_offset_Y)*Main_magnifier_factor;
  short real_width=width*Main_magnifier_factor;
  short end_y_pos=(real_y_pos+Main_magnifier_factor<Menu_Y)?real_y_pos+Main_magnifier_factor:Menu_Y;
  short index;

  for (index=real_y_pos; index<end_y_pos; index++)
    Horizontal_XOR_line(real_x_pos,index,real_width);

  Update_rect(real_x_pos,real_y_pos,real_width,end_y_pos-real_y_pos);
}
