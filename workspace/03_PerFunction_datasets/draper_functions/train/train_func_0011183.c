scrollBackground()
{
  move_background_x--;
  if((int) move_background_x < -((int) map.background_image->w))
    move_background_x = 0;
  move_background_y--;
  if((int) move_background_y < -((int) map.background_image->h))
    move_background_y = 0;
}
