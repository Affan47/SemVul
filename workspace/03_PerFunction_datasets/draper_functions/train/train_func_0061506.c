base_name (char const *name)
{
  char const *base = last_component (name);
  size_t length;


  if (! *base)
    return xstrndup (name, base_len (name));


  length = base_len (base);
  if (ISSLASH (base[length]))
    length++;


  if (FILE_SYSTEM_PREFIX_LEN (base))
    {
      char *p = xmalloc (length + 3);
      p[0] = '.';
      p[1] = '/';
      memcpy (p + 2, base, length);
      p[length + 2] = '\0';
      return p;
    }


  return xstrndup (base, length);
}
