m68hc11_strip_name_encoding (str)
     const char *str;
{
  return str + (*str == '*' || *str == '@' || *str == '&');
}
