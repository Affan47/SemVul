dyn_string_append_cstr (dyn_string_t dest, const char *s)
{
  int len = strlen (s);


  if (dyn_string_resize (dest, dest->length + len) == NULL)
    return 0;
  strcpy (dest->s + dest->length, s);
  dest->length += len;
  return 1;
}
