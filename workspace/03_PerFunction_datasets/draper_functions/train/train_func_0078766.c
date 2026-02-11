MakeCidentifier(const std::string& s)
{
  std::string str(s);
  if (str.find_first_of("0123456789") == 0) {
    str = "_" + str;
  }

  std::string permited_chars("_"
                             "abcdefghijklmnopqrstuvwxyz"
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             "0123456789");
  std::string::size_type pos = 0;
  while ((pos = str.find_first_not_of(permited_chars, pos)) !=
         std::string::npos) {
    str[pos] = '_';
  }
  return str;
}
