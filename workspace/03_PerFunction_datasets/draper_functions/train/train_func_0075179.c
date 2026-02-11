array_append_string_unique(const char *str,
                                   const char **array, size_t size)
{
  const char **p;

  const char **end= array + size - 1;
  DBUG_ASSERT(*end == NULL);

  for (p= array; *p; ++p)
  {
    if (strcmp(*p, str) == 0)
      break;
  }
  if (p >= end)
    return TRUE;

  DBUG_ASSERT(*p == NULL || strcmp(*p, str) == 0);

  while (*(p + 1))
  {
    *p= *(p + 1);
    ++p;
  }

  DBUG_ASSERT(p < end);
  *p= str;

  return FALSE;
}
