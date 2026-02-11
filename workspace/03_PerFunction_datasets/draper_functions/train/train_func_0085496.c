restore_game(uint16_t address, uint16_t length, char *filename,
    bool skip_asking_for_filename, bool evaluate_result, char *directory)
{
  z_file *save_file;
  char *str;
  char *system_filename;

  TRACE_LOG("Restore %d bytes to address %d.\n", length, address);

  if (filename != NULL)
  {
    if (bool_equal(skip_asking_for_filename, true))
    {
      system_filename = filename;
      if (directory != NULL)
      {
        str = fizmo_malloc(strlen(directory) + strlen(system_filename) + 2);
        strcpy(str, directory);
        strcat(str, "/");
        strcat(str, system_filename);
      }
      else
        str = system_filename;
      save_file = open_simple_iff_file(
          str,
          IFF_MODE_READ_SAVEGAME);
      if (directory != NULL)
        free(str);
      free(system_filename);
    }
    else
    {
      if ( ((ask_for_filename(NULL, &save_file, directory,
                FILETYPE_SAVEGAME, FILEACCESS_READ)) < 0)
        || (save_file == NULL) )
      {
        if (bool_equal(evaluate_result, true))
          _store_save_or_restore_result(0);
        return -1;
      }
      str = save_file->filename;
      TRACE_LOG("filename from ask_for_filename: \"%s\".\n", str);
    }
  }
  else
  {
    if ( ((ask_for_filename(NULL, &save_file, directory,
              FILETYPE_SAVEGAME, FILEACCESS_READ)) < 0)
        || (save_file == NULL) )
    {
      if (bool_equal(evaluate_result, true))
        _store_save_or_restore_result(0);
      return -1;
    }
    str = save_file->filename;
    TRACE_LOG("filename from ask_for_filename: \"%s\".\n", str);
  }

  return restore_game_from_stream(address, length, save_file, evaluate_result);
}
