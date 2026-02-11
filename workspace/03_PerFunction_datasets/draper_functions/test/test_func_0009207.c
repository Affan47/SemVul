Button_Layer_get_transparent(void)
{
  Hide_cursor();

  if (Main_backups->Pages->Transparent_color != Back_color)
  {
    Set_back_color(Main_backups->Pages->Transparent_color);
  }

  Unselect_button(BUTTON_LAYER_COLOR);
  Display_cursor();
}
