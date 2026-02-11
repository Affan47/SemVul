str_int(char *s,
	    int *np)
{
  int i, sign, n;

  i = 0;
  sign = 1;
  if (s[0] == '+' || s[0] == '-') {
    if (s[0] == '-')
      sign = -1;
    i = 1;
  }
  if (s[i] == '\0')
    return(0);
  else {
    n = 0;
    for( ; s[i] >= '0' && s[i] <= '9'; i++)
      n = n * 10 + s[i] - '0';
    *np = n * sign;
    return(s[i] == '\0');
  }
}
