BaseName ( const jalib::string& str )
{
  size_t len = str.length();

  if (str == "/" || str == "." || str == ".." || str.empty())
    return str;


  while (len > 0 && str[len - 1] == '/') {
    len--;
  }

  size_t lastSlash = str.find_last_of('/', len);

  if (lastSlash == string::npos)
    return str.substr(0, len);

  return str.substr(lastSlash + 1, len - lastSlash);
}
