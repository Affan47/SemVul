cvtToInt (const char *str, int *value)
{

    const char *p = str;
    int error = 0;
    int digits = 0;
    int sign = 0;
    while (*p != '\0')
      {
	  if (*p >= '0' && *p <= '9')
	      digits++;
	  else if (*p == '-' || *p == '+')
	    {
		if (digits == 0)
		    sign++;
		else
		    error = 1;
	    }
	  else
	      error = 1;
	  p++;
      }
    if (digits > 0 && sign < 2 && error == 0)
      {
	  *value = atoi (str);
	  return 1;
      }
    return 0;
}
