make_string (unsigned char **data, unsigned long len)
{
  GString *s;
  unsigned long i;

  if (len < 1)
    {
      return g_strdup ("\0");
    }

  s = g_string_new ("");


  for (i = 0; i < len; i++)
    {
      g_string_append_printf (s, "%.2X", (*data)[i]);


      if (!((i + 1) % 4) && i && ((i + 1) % 16) && i != len - 1)
        {
          g_string_append_c (s, 0x20);
        }


      if (!((i + 1) % 16) && i && i != len - 1)
        {
          g_string_append_c (s, 0x0A);
        }
      else if (i != len - 1)
        {
          g_string_append_c (s, 0x20);
        }
    }

  return s->str;
}
