indent(short indent_size, short indent_level)
{
  const int MAX_INDENT = 80;
  static char buffer[1 + MAX_INDENT];

  int indent = indent_size * indent_level;

  if (indent > MAX_INDENT)
    indent = MAX_INDENT;

  for (int i = 0; i < indent; i++)
    buffer[i] = ' ';

  buffer[indent] = '\0';

  return buffer;
}
