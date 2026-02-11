atoi_octal(const char *str)
{
  long int tmp;
  while (*str && my_isspace(&my_charset_latin1, *str))
    str++;
  str2int(str,
	  (*str == '0' ? 8 : 10),
	  0, INT_MAX, &tmp);
  return (ulong) tmp;
}
