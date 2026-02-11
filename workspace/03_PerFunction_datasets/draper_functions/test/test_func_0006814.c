ieee_start_compilation_unit (p, filename)
     PTR p;
     const char *filename;
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  const char *modname;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  const char *backslash;
#endif
  char *c, *s;
  unsigned int nindx;

  if (info->filename != NULL)
    {
      if (! ieee_finish_compilation_unit (info))
	return FALSE;
    }

  info->filename = filename;
  modname = strrchr (filename, '/');
#ifdef HAVE_DOS_BASED_FILE_SYSTEM

  backslash = strrchr (filename, '\\');
  if (modname == NULL || (backslash != NULL && backslash > modname))
    modname = backslash;
#endif

  if (modname != NULL)
    ++modname;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  else if (filename[0] && filename[1] == ':')
    modname = filename + 2;
#endif
  else
    modname = filename;

  c = xstrdup (modname);
  s = strrchr (c, '.');
  if (s != NULL)
    *s = '\0';
  info->modname = c;

  if (! ieee_init_buffer (info, &info->types)
      || ! ieee_init_buffer (info, &info->vars)
      || ! ieee_init_buffer (info, &info->cxx)
      || ! ieee_init_buffer (info, &info->linenos))
    return FALSE;
  info->ranges = NULL;


  if (! ieee_change_buffer (info, &info->types)
      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
      || ! ieee_write_byte (info, 1)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_id (info, info->modname))
    return FALSE;

  nindx = info->name_indx;
  ++info->name_indx;
  if (! ieee_change_buffer (info, &info->vars)
      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
      || ! ieee_write_byte (info, 3)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_id (info, info->modname))
    return FALSE;

  return TRUE;
}
