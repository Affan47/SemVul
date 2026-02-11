str_get_basename (str_t to, const str_t from, int dirsep)
{
  const char * ptr = strrchr (CSTR(from), dirsep);

  if (ptr == NULL)
    str_copy_c (to, CSTR(from));
  else
    str_copy_c (to, ptr + 1);
}
