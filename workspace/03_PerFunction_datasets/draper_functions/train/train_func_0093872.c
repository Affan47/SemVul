Position_screen_according_to_position(int target_x, int target_y)
{

  if (Main_image_width>Main_separator_position)
  {
    Main_offset_X=target_x-Mouse_X;


    if (Main_magnifier_offset_X<Main_offset_X)
      Main_offset_X=Main_magnifier_offset_X;
    else if (Main_magnifier_offset_X+Main_magnifier_width > Main_offset_X+Main_separator_position)
      Main_offset_X = Main_magnifier_offset_X+Main_magnifier_width-Main_separator_position;
    if (Main_offset_X<0)
      Main_offset_X=0;
    else if (Main_image_width<Main_offset_X+Main_separator_position)
      Main_offset_X=Main_image_width-Main_separator_position;


  }
  else
    Main_offset_X=0;


  if (Main_image_height>Menu_Y)
  {
    Main_offset_Y=target_y-Mouse_Y;


    if (Main_magnifier_offset_Y<Main_offset_Y)
      Main_offset_Y=Main_magnifier_offset_Y;
    else if (Main_magnifier_offset_Y+Main_magnifier_height > Main_offset_Y)
      Main_offset_Y = Main_magnifier_offset_Y+Main_magnifier_height;
    if (Main_offset_Y<0)
      Main_offset_Y=0;
    else if (Main_image_height<Main_offset_Y+Menu_Y)
      Main_offset_Y=Main_image_height-Menu_Y;
  }
  else
    Main_offset_Y=0;
}
