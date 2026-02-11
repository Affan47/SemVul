utf8_string_to_zucs_string(z_ucs *dest, char *src, int max_dest_size)
{
  if (max_dest_size < 1)
    return NULL;

  while (*src != (char)0)
  {
    if (max_dest_size == 1)
    {
      *dest = 0;
      return src;
    }

    *dest = utf8_char_to_zucs_char(&src);
    max_dest_size--;
    dest++;
  }

  *dest = 0;

  return NULL;
}
