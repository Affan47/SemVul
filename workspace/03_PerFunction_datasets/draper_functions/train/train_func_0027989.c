check_column_name(const char *name)
{

  size_t name_length= 0;
  bool last_char_is_space= TRUE;

  while (*name)
  {
#if defined(USE_MB) && defined(USE_MB_IDENT)
    last_char_is_space= my_isspace(system_charset_info, *name);
    if (use_mb(system_charset_info))
    {
      int len=my_ismbchar(system_charset_info, name,
                          name+system_charset_info->mbmaxlen);
      if (len)
      {
        name += len;
        name_length++;
        continue;
      }
    }
#else
    last_char_is_space= *name==' ';
#endif
    if (*name == NAMES_SEP_CHAR)
      return 1;
    name++;
    name_length++;
  }

  return last_char_is_space || (name_length > NAME_CHAR_LEN);
}
