get_key_relative(const gchar* key, const gchar* dir)
{
  int i;

  g_assert(key != NULL);
  g_assert(dir != NULL);

  i = 0;
  while (dir [i])
    {
      if (dir [i] != key [i])
        return key;
      ++i;
    }

  if (key [i] != '/' || key [i] == '\0')
    return key;

  ++i;

  return key + i;
}
