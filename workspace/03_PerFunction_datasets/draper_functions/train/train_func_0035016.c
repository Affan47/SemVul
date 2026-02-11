readLine(DataSource &source)
{
  String s;
  int ch = source.getChar();
  while (ch != EOF && ch != '\n') {
    s += char(ch);
    ch = source.getChar();
  }
  return s;
}
