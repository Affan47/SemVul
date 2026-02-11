ends_with(const string line, const string suffix)
{
  int n1 = strlen(line), n2 = strlen(suffix);
  return n1 >= n2 && eq(line + n1 - n2, suffix);
}
