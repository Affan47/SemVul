valid_utf8(const char *s)
{
  while (*s)
  {
    if (*s & 0x80)
    {


      if ((*s & 0xc0) == 0x80)
        return (0);
      else if ((*s & 0xe0) == 0xc0)
      {


        s ++;

        if ((*s & 0xc0) != 0x80)
          return (0);
      }
      else if ((*s & 0xf0) == 0xe0)
      {


        s ++;

        if ((*s & 0xc0) != 0x80)
          return (0);

        s ++;

        if ((*s & 0xc0) != 0x80)
          return (0);
      }
      else if ((*s & 0xf8) == 0xf0)
      {


        s ++;

        if ((*s & 0xc0) != 0x80)
          return (0);

        s ++;

        if ((*s & 0xc0) != 0x80)
          return (0);

        s ++;

        if ((*s & 0xc0) != 0x80)
          return (0);
      }
      else
        return (0);
    }

    s ++;
  }

  return (1);
}
