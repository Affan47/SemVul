get_file_function_name_long (const char *type)
{
  char *buf;
  const char *p;
  char *q;

  if (first_global_object_name)
    p = first_global_object_name;
  else
    {


      unsigned len;
      const char *name = weak_global_object_name;
      const char *file = main_input_filename;

      if (! name)
	name = "";
      if (! file)
	file = input_filename;

      len = strlen (file);
      q = alloca (9 * 2 + len + 1);
      memcpy (q, file, len + 1);
      clean_symbol_name (q);

      sprintf (q + len, "_%08X_%08X", crc32_string (0, name),
	       crc32_string (0, flag_random_seed));

      p = q;
    }

  buf = alloca (sizeof (FILE_FUNCTION_FORMAT) + strlen (p) + strlen (type));


  sprintf (buf, FILE_FUNCTION_FORMAT, type, p);

  return get_identifier (buf);
}
