print_if_flags (int flags, const char *avoid, char separator)
{
  int f = 1;
  const char *name;
  int first = 1;
  int length = 0;

  while (flags && f)
    {
      if (f & flags)
	{
	  name = if_flagtoname (f, avoid);
	  if (name)
	    {
	      if (!first)
		{
		  putchar (separator);
		  length++;
		}
	      length += printf ("%s", name);
	      flags &= ~f;
	      first = 0;
	    }
	}
      f = f << 1;
    }
  if (flags)
    {
      if (!first)
	{
	  putchar (separator);
	  length++;
	}
      length += printf ("%#x", flags);
    }
  return length;
}
