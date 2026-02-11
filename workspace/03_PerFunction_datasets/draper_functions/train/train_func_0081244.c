_gftp_convert_from_newlines (char *str)
{
  char *stpos, *endpos, *ret, savechar;
  size_t len;

  ret = g_strdup ("");
  len = 0;

  for (stpos = str;
       (endpos = strchr (stpos, '\n')) != NULL;
       stpos = endpos + 1)
    {
      savechar = *endpos;
      *endpos = '\0';

      len += strlen (stpos) + 2;
      ret = g_realloc (ret, (gulong) len + 1);
      strcat (ret, stpos);
      strcat (ret, "%n");

      *endpos = savechar;
    }

  if (stpos != NULL && *stpos != '\0')
    {
      len += strlen (stpos);
      ret = g_realloc (ret, (gulong) len + 1);
      strcat (ret, stpos);
    }

  return (ret);
}
