atof_nonlocalized(const char *str)
{
  int i=0, dot_pos=-1, decimals=0, sign=1;

  double value, value2=0.0;


  value = atoi_nonlocalized(str);

  while(str[i] == ' ')
  {
    i++;
  }

  if((str[i] == '+') || (str[i] == '-'))
  {
    if(str[i] == '-')
    {
      sign = -1;
    }

    i++;
  }

  for(; ; i++)
  {
    if(str[i] == 0)
    {
      break;
    }

    if(((str[i] < '0') || (str[i] > '9')) && (str[i] != '.'))
    {
      break;
    }

    if(dot_pos >= 0)
    {
      if((str[i] >= '0') && (str[i] <= '9'))
      {
        decimals++;
      }
      else
      {
        break;
      }
    }

    if(str[i] == '.')
    {
      if(dot_pos < 0)
      {
        dot_pos = i;
      }
    }
  }

  if(decimals)
  {
    value2 = atoi_nonlocalized(str + dot_pos + 1) * sign;

    i = 1;

    while(decimals--)
    {
      i *= 10;
    }

    value2 /= i;
  }

  return(value + value2);
}
