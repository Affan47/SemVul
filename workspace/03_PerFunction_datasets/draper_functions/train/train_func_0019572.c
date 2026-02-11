is_number (char const *str)
{
  if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
      str += 2;
      str += strspn (str, "0123456789aAbBcCdDeEfF");
    }
  else {
    size_t offn;
    str += (offn = strspn (str, "0123456789"));
    if (offn)
      str += strspn (str, "uUlL");
  }
  return (*str == '\0');
}
