explode_filename(const char *filename, int number, const char *name, int max_nimages)
{
  static char *s;
  int l = strlen(filename);
  l += name ? strlen(name) : 10;

  Gif_Delete(s);
  s = Gif_NewArray(char, l + 3);
  if (name)
    sprintf(s, "%s.%s", filename, name);
  else if (max_nimages <= 1000)
    sprintf(s, "%s.%03d", filename, number);
  else {
    int digits;
    unsigned j;
    unsigned max = (max_nimages < 0 ? 0 : max_nimages);
    for (digits = 4, j = 10000; max > j; digits++)
      j *= 10;
    sprintf(s, "%s.%0*d", filename, digits, number);
  }

  return s;
}
