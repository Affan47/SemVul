max_length (size_t *width, const char *str)
{
  size_t len = strlen (str);
  if (len > *width)
    *width = len;
}
