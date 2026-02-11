fmtulong (ui, base, buf, len, flags)
     UNSIGNED_LONG ui;
     int base;
     char *buf;
     size_t len;
     int flags;
{
  char *p;
  int sign;
  LONG si;

  if (base == 0)
    base = 10;

  if (base < 2 || base > 64)
    {
#if 1
      strncpy (buf, _("invalid base"), len - 1);
      buf[len] = '\0';
      errno = EINVAL;
      return (p = buf);
#else
      base = 10;
#endif
    }

  sign = 0;
  if ((flags & FL_UNSIGNED) == 0 && (LONG)ui < 0)
    {
      ui = -ui;
      sign = '-';
    }

  p = buf + len - 2;
  p[1] = '\0';


  switch (base)
    {
    case 10:
      if (ui < 10)
	{
	  *p-- = TOCHAR (ui);
	  break;
	}


      if ((LONG)ui < 0)
	{
	  *p-- = TOCHAR (ui % 10);
	  si = ui / 10;
	}
      else
        si = ui;
      do
	*p-- = TOCHAR (si % 10);
      while (si /= 10);
      break;

    case 8:
      do
	*p-- = TOCHAR (ui & 7);
      while (ui >>= 3);
      break;

    case 16:
      do
	*p-- = (flags & FL_HEXUPPER) ? X_digs[ui & 15] : x_digs[ui & 15];
      while (ui >>= 4);
      break;

    case 2:
      do
	*p-- = TOCHAR (ui & 1);
      while (ui >>= 1);
      break;

    default:
      do
	*p-- = FMTCHAR (ui % base);
      while (ui /= base);
      break;
    }

  if ((flags & FL_PREFIX) && (base == 8 || base == 16))
    {
      if (base == 16)
	{
	  *p-- = (flags & FL_HEXUPPER) ? 'X' : 'x';
	  *p-- = '0';
	}
      else if (p[1] != '0')
	*p-- = '0';
    }
  else if ((flags & FL_ADDBASE) && base != 10)
    {
      *p-- = '#';
      *p-- = TOCHAR (base % 10);
      if (base > 10)
        *p-- = TOCHAR (base / 10);
    }

  if (sign)
    *p-- = '-';

  return (p + 1);
}
