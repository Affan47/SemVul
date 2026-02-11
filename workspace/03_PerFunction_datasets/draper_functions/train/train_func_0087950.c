plugin_name (const char *str)
{
  char *buf, *p;
  static const char prefix[] = PLUGIN_DIR "sasl-";

  assert (str != NULL);

  buf = malloc (sizeof prefix + strlen (str) + sizeof DLEXT);
  if (buf == NULL)
    return NULL;
  strcpy (buf, prefix);
  p = buf + sizeof prefix - 1;
  while (*str != '\0')
    *p++ = tolower (*str++);
  strcpy (p, DLEXT);
  return buf;
}
