matches_main_base (const char *path)
{

  static const char *last_path = NULL;
  static int last_match = 0;
  if (path != last_path)
    {
      const char *base;
      int length = base_of_path (path, &base);
      last_path = path;
      last_match = (length == main_input_baselength
                    && memcmp (base, main_input_basename, length) == 0);
    }
  return last_match;
}
