count_lines(source, count)
  char *source;
  long count;
{
  char *i;
  long j = 0;

  for (i = source; i < source + count; i++) if (*i == '\n') j++;
  return j;
}
