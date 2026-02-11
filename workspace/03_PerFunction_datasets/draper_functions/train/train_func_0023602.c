containsLine(int line) const
{
  return (line > start().line() || (line == start().line() && !start().column())) && line < end().line();
}
