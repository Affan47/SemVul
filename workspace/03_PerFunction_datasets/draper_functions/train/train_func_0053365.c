cp_is_click_id(const String &str)
{
  const unsigned char *s = reinterpret_cast<const unsigned char*>(str.data());
  int len = str.length();
  for (int i = 0; i < len; i++)
    if (isalnum(s[i]) || s[i] == '_' || s[i] == '@')
      ;
    else if (s[i] != '/' || i == 0 || i == len - 1 || s[i+1] == '/')
      return false;
  return len > 0;
}
