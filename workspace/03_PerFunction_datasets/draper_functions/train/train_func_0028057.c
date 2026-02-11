tab_to (FILE *out, int from, int to)
{
  int tab_width = 8;
  int to_mod = (to / tab_width) * tab_width;
  while (from < to_mod)
    {
      fprintf(out, "\t");
      from = (((from / tab_width) + 1) * tab_width);
    }
  while (from < to)
    {
      fprintf(out, " ");
      from++;
    }
  return from;
}
