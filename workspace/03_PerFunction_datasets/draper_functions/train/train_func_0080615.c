Button_Autosave(void)
{
  byte old_cursor_shape;
  static char filename[MAX_PATH_CHARACTERS];
  byte file_already_exists;


  Get_full_filename(filename, Main_backups->Pages->Filename, Main_backups->Pages->File_directory);
  file_already_exists=File_exists(filename);

  if ( (!file_already_exists) || Confirmation_box("Erase old file ?") )
  {
    if ((file_already_exists) && (Config.Backup))
      Backup_existing_file();
    else
      File_error=0;

    Hide_cursor();

    if (!File_error)
    {
      T_IO_Context save_context;

      old_cursor_shape=Cursor_shape;
      Cursor_shape=CURSOR_SHAPE_HOURGLASS;
      Display_cursor();

      Init_context_layered_image(&save_context, Main_backups->Pages->Filename, Main_backups->Pages->File_directory);
      Save_image(&save_context);
      if (!File_error)
      {
        Main_image_is_modified=0;
      }
      Destroy_context(&save_context);

      Hide_cursor();
      Cursor_shape=old_cursor_shape;
    }
    else
      Error(0);
  }
  else
    Hide_cursor();

  Unselect_button(BUTTON_SAVE);

  Display_cursor();
}
