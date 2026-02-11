get_vernumber(const char *version)
{
  int		numbers[4],
		nnumbers,
		temp,
		offset;
  const char	*ptr;


  memset(numbers, 0, sizeof(numbers));

  for (ptr = version; *ptr && !isdigit(*ptr & 255); ptr ++);


  for (offset = 0, temp = 0, nnumbers = 0; *ptr && !isspace(*ptr & 255); ptr ++)
    if (isdigit(*ptr & 255))
      temp = temp * 10 + *ptr - '0';
    else
    {


      if (nnumbers < 4)
      {
        numbers[nnumbers] = temp;
	nnumbers ++;
      }

      temp = 0;

      if (*ptr == '.')
	offset = 0;
      else if (*ptr == 'p' || *ptr == '-')
      {
	if (strncmp(ptr, "pre", 3) == 0)
	{
	  ptr += 2;
	  offset = -20;
	}
	else
	  offset = 0;

        nnumbers = 3;
      }
      else if (*ptr == 'b')
      {
	offset   = -50;
        nnumbers = 3;
      }
      else
      {
	offset   = -100;
        nnumbers = 3;
      }
    }

  if (nnumbers < 4)
    numbers[nnumbers] = temp;


  return (((numbers[0] * 100 + numbers[1]) * 100 + numbers[2]) * 100 +
          numbers[3] + offset);
}
