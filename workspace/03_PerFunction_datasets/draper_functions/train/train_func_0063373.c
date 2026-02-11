window_physical_lines (NODE *node)
{
  register int i, lines;
  char *contents;

  if (!node)
    return 0;

  contents = node->contents;
  for (i = 0, lines = 1; i < node->nodelen; i++)
    if (contents[i] == '\n')
      lines++;

  return lines;
}
