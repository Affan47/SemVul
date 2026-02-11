path_concat (const char *dir, const char *base, char **base_in_result)
{
  char *p;
  char *p_concat;
  size_t base_len;
  size_t dir_len;

  if (!dir)
    {
      p_concat = strdup (base);
      if (base_in_result)
        *base_in_result = p_concat;
      return p_concat;
    }


  base_len = strlen (base);
  dir_len = strlen (dir);


  p_concat = (char *) malloc (dir_len + base_len + 2);
  if (!p_concat)
    return 0;

  p = mempcpy (p_concat, dir, dir_len);

  if (ISSLASH (*(p - 1)) && ISSLASH(*base))
    --p;
  else if (!ISSLASH (*(p - 1)) && !ISSLASH(*base))
    *p++ = DIRECTORY_SEPARATOR;

  if (base_in_result)
    *base_in_result = p;

  memcpy (p, base, base_len + 1);

  return p_concat;
}
