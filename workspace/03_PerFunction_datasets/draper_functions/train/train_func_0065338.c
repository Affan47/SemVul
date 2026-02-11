my_strnchr (const char *s, size_t count, int c)
{
  size_t i;

  for (i = 0; i < count; i++)
    if (*(s + i) == (const char) c)
      return (char *) (s + i);

  return NULL;
}
