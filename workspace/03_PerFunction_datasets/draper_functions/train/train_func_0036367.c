my_casedn_str_mb(CHARSET_INFO * cs, char *str)
{
  register uint32 l;
  register uchar *map= cs->to_lower;
  char *str_orig= str;

  while (*str)
  {

    if ((l= my_ismbchar(cs, str, str + cs->mbmaxlen)))
      str+= l;
    else
    {
      *str= (char) map[(uchar)*str];
      str++;
    }
  }
  return (size_t) (str - str_orig);
}
