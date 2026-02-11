fraccompare (a, b)
     register char *a, *b;
{
  register int tmpa = UCHAR (*a), tmpb = UCHAR (*b);

  if (tmpa == '.' && tmpb == '.')
    {
      do
	tmpa = UCHAR (*++a), tmpb = UCHAR (*++b);
      while (tmpa == tmpb && digits[tmpa]);
      if (digits[tmpa] && digits[tmpb])
	return tmpa - tmpb;
      if (digits[tmpa])
	{
	  while (tmpa == '0')
	    tmpa = UCHAR (*++a);
	  if (digits[tmpa])
	    return 1;
	  return 0;
	}
      if (digits[tmpb])
	{
	  while (tmpb == '0')
	    tmpb = UCHAR (*++b);
	  if (digits[tmpb])
	    return -1;
	  return 0;
	}
      return 0;
    }
  else if (tmpa == '.')
    {
      do
	tmpa = UCHAR (*++a);
      while (tmpa == '0');
      if (digits[tmpa])
	return 1;
      return 0;
    }
  else if (tmpb == '.')
    {
      do
	tmpb = UCHAR (*++b);
      while (tmpb == '0');
      if (digits[tmpb])
	return -1;
      return 0;
    }
  return 0;
}
