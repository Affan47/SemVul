open_simple_iff_file(char *filename, int mode)
{
  z_file *iff_file;

  if (filename == NULL)
    return NULL;

  TRACE_LOG("Trying to open IFF file \"%s\".\n", filename);

  current_mode = mode;

  if ( (mode == IFF_MODE_READ) || (mode == IFF_MODE_READ_SAVEGAME) )
  {
    iff_file
      = mode == IFF_MODE_READ_SAVEGAME
      ? fsi->openfile(filename, FILETYPE_SAVEGAME, FILEACCESS_READ)
      : fsi->openfile(filename, FILETYPE_DATA, FILEACCESS_READ);

    if (iff_file == NULL)
      return NULL;

    if (detect_simple_iff_stream(iff_file) == false)
    {
      (void)fsi->closefile(iff_file);
      return NULL;
    }
  }
  else if ( (mode == IFF_MODE_WRITE) || (mode == IFF_MODE_WRITE_SAVEGAME) )
  {
    iff_file
      = mode == IFF_MODE_WRITE_SAVEGAME
      ? fsi->openfile(filename, FILETYPE_SAVEGAME, FILEACCESS_WRITE)
      : fsi->openfile(filename, FILETYPE_DATA, FILEACCESS_WRITE);

    if (iff_file == NULL)
      return NULL;

    if (init_empty_file_for_iff_write(iff_file) == -1)
    {
      (void)fsi->closefile(iff_file);
      return NULL;
    }
  }
  else
  {
    i18n_translate_and_exit(
        libfizmo_module_name,
        i18n_libfizmo_INVALID_IFF_ACCESS_MODE_P0D,
        -1,
        (long int)mode);

    return NULL;

  }

  return iff_file;
}
