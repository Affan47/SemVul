print_sanitized_buffer2 (FILE *fp, const void *buffer, size_t length,
                         int delim, int delim2)
{
  const unsigned char *p = buffer;
  size_t count = 0;

  for (; length; length--, p++, count++)
    {
      if (*p < 0x20
          || *p == 0x7f
          || *p == delim
          || *p == delim2
          || ((delim || delim2) && *p=='\\'))
        {
          putc ('\\', fp);
          count++;
          if (*p == '\n')
            {
              putc ('n', fp);
              count++;
            }
          else if (*p == '\r')
            {
              putc ('r', fp);
              count++;
            }
          else if (*p == '\f')
            {
              putc ('f', fp);
              count++;
            }
          else if (*p == '\v')
            {
              putc ('v', fp);
              count++;
            }
          else if (*p == '\b')
            {
              putc ('b', fp);
              count++;
            }
          else if (!*p)
            {
              putc('0', fp);
              count++;
            }
          else
            {
              fprintf (fp, "x%02x", *p);
              count += 3;
            }
	}
      else
        {
          putc (*p, fp);
          count++;
        }
    }

  return count;
}
