dyn_string_insert_cstr (dest, pos, src)
     dyn_string_t dest;
     int pos;
     const char *src;
{
  int i;
  int length = strlen (src);

  if (dyn_string_resize (dest, dest->length + length) == NULL)
    return 0;

  for (i = dest->length; i >= pos; --i)
    dest->s[i + length] = dest->s[i];

  strncpy (dest->s + pos, src, length);

  dest->length += length;
  return 1;
}
