Tag_used_colors(byte color, dword color_usage[])
{
  word index;

  for (index=0;index<=255;index++)
  {
    short x_pos=Window_palette_button_list->Pos_X+6+((index>>4)*10);
    short y_pos=Window_palette_button_list->Pos_Y+3+((index&15)* 5);
    byte col;

    col=(color&&color_usage[index])?MC_White:MC_Light;
    Window_rectangle(x_pos+5,y_pos+0,1,5,col);
  }

  Update_window_area(Window_palette_button_list->Pos_X+3,Window_palette_button_list->Pos_Y+3,12*16,5*16);
}
