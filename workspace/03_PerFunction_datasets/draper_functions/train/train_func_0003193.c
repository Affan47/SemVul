Button_Layer_set_transparent(void)
{
  Hide_cursor();

  if (Main_backups->Pages->Transparent_color != Back_color)
  {
    Backup_layers(-1);
    Main_backups->Pages->Transparent_color = Back_color;

    Redraw_layered_image();
    Display_all_screen();
    End_of_modification();
  }

  Unselect_button(BUTTON_LAYER_COLOR);
  Display_cursor();
}
