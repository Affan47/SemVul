special (register char *s)
{
  register char c;
  char b;

  switch (*s)
    {
    case '^':
      b = *++s;
      if (b == '?')
	{
	  c = b | 0x40;
	}
      else
	{
	  c = b & 0x1f;
	}
      break;
    default:
      c = *s;
      break;
    }
  return c;
}
