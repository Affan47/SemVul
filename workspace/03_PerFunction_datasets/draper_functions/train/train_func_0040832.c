out_file_list (void)
{
  size_t size;
  const char *dir;
  char *cp;
  unsigned int i;


  for (i = 1; i < dirs_in_use; ++i)
    {
      dir = remap_debug_filename (dirs[i]);
      size = strlen (dir) + 1;
      cp = frag_more (size);
      memcpy (cp, dir, size);
    }

  out_byte ('\0');

  for (i = 1; i < files_in_use; ++i)
    {
      const char *fullfilename;

      if (files[i].filename == NULL)
	{
	  as_bad (_("unassigned file number %ld"), (long) i);

	  files[i].filename = "";
	  continue;
	}

      fullfilename = DWARF2_FILE_NAME (files[i].filename,
				       files[i].dir ? dirs [files [i].dir] : "");
      size = strlen (fullfilename) + 1;
      cp = frag_more (size);
      memcpy (cp, fullfilename, size);

      out_uleb128 (files[i].dir);

      out_uleb128 (DWARF2_FILE_TIME_NAME (files[i].filename,
				          files[i].dir ? dirs [files [i].dir] : ""));

      out_uleb128 (DWARF2_FILE_SIZE_NAME (files[i].filename,
				          files[i].dir ? dirs [files [i].dir] : ""));
    }


  out_byte (0);
}
