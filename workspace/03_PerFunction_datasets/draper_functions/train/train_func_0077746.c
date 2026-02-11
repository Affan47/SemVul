rl_copy_text (from, to)
     int from, to;
{
  register int length;
  char *copy;


  if (from > to)
    SWAP (from, to);

  length = to - from;
  copy = (char *)xmalloc (1 + length);
  strncpy (copy, rl_line_buffer + from, length);
  copy[length] = '\0';
  return (copy);
}
