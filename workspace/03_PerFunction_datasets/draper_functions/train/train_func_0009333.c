split(const Text &text,
			 Char space,
			 Vector<StringC> &tokens,
			 Vector<size_t> &tokensPos)
{
  const StringC &str = text.string();
  for (size_t i = 0;;) {
    for (; i < str.size() && str[i] == space; i++)
      ;
    if (i >= str.size())
      break;
    size_t start = i;
    for (; i < str.size() && str[i] != space; i++)
      ;
    tokens.push_back(StringC(str.data() + start, i - start));
    tokensPos.push_back(start);
  }
}
