Window_display_icon_sprite(word x_pos,word y_pos,byte type)
{
  word i,j;

  for (j=0; j<ICON_SPRITE_HEIGHT; j++)
    for (i=0; i<ICON_SPRITE_WIDTH; i++)
      Pixel_in_window(x_pos+i,y_pos+j,Gfx->Icon_sprite[type][j][i]);
  Update_rect(ToWinX(x_pos),ToWinY(y_pos),ToWinL(ICON_SPRITE_WIDTH),ToWinH(ICON_SPRITE_HEIGHT));
}
