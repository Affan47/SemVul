WriteString(const std::string &path,
                 const char *s)
{
  std::string _s(s);
  WriteString(path,_s);
}
