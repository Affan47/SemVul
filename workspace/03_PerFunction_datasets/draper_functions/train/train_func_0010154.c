GetNumTerminals() const
{
  size_t ret = 0;

  for (size_t pos = 0; pos < GetSize(); ++pos) {
    if (!GetWord(pos).IsNonTerminal())
      ret++;
  }
  return ret;
}
