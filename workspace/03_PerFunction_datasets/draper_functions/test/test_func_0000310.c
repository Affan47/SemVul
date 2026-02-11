process_file (const char *file_name)
{
  FILE * file;
  char armag[SARMAG];
  int ret;

  if (check_file (file_name, NULL))
    return 1;

  file = fopen (file_name, "r+b");
  if (file == NULL)
    {
      error (_("Input file '%s' is not readable\n"), file_name);
      return 1;
    }

  if (fread (armag, SARMAG, 1, file) != 1)
    {
      error (_("%s: Failed to read file's magic number\n"),
		 file_name);
      fclose (file);
      return 1;
    }

  if (memcmp (armag, ARMAG, SARMAG) == 0)
    ret = process_archive (file_name, file, FALSE);
  else if (memcmp (armag, ARMAGT, SARMAG) == 0)
    ret = process_archive (file_name, file, TRUE);
  else
    {
      rewind (file);
      archive_file_size = archive_file_offset = 0;
      ret = process_object (file_name, file);
    }

  fclose (file);

  return ret;
}
