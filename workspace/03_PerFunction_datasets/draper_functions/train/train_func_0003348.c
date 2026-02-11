splitString (const std::string &text,
             const std::string &separators,
             std::vector<std::string> &words)
{
  const std::string::size_type n = text.length();
  std::string::size_type start = text.find_first_not_of(separators);
  while (start < n)
    {
    std::string::size_type stop = text.find_first_of(separators, start);
    if (stop > n) stop = n;
    words.push_back(text.substr(start, stop - start));
    start = text.find_first_not_of(separators, stop+1);
    }
}
