read_assuan (int fd)
{


  static char pending[MAX_LINELEN];
  static size_t pending_len;
  size_t nleft = sizeof recv_line;
  char *buf = recv_line;
  char *p;

  while (nleft > 0)
    {
      int n;

      if (pending_len)
        {
          if (pending_len >= nleft)
            die_0 ("received line too large");
          memcpy (buf, pending, pending_len);
          n = pending_len;
          pending_len = 0;
        }
      else
        {
          do
            {
              n = read (fd, buf, nleft);
            }
          while (n < 0 && errno == EINTR);
        }

      if (opt_verbose && n >= 0 )
	{
	  int i;

	  printf ("%s: read \"", __func__);
	  for (i = 0; i < n; i ++)
	    putc (buf[i], stdout);
	  printf ("\"\n");
	}

      if (n < 0)
        die_2 ("reading fd %d failed: %s", fd, strerror (errno));
      else if (!n)
        die_1 ("received incomplete line on fd %d", fd);
      p = buf;
      nleft -= n;
      buf += n;

      for (; n && *p != '\n'; n--, p++)
        ;
      if (n)
        {
          if (n>1)
            {
              n--;
              memcpy (pending, p + 1, n);
              pending_len = n;
            }
	  *p = '\0';
          break;
        }
    }
  if (!nleft)
    die_0 ("received line too large");

  p = recv_line;
  if (p[0] == 'O' && p[1] == 'K' && (p[2] == ' ' || !p[2]))
    {
      recv_type = LINE_OK;
      p += 3;
    }
  else if (p[0] == 'E' && p[1] == 'R' && p[2] == 'R'
           && (p[3] == ' ' || !p[3]))
    {
      recv_type = LINE_ERR;
      p += 4;
    }
  else if (p[0] == 'S' && (p[1] == ' ' || !p[1]))
    {
      recv_type = LINE_STAT;
      p += 2;
    }
  else if (p[0] == 'D' && p[1] == ' ')
    {
      recv_type = LINE_DATA;
      p += 2;
    }
  else if (p[0] == 'E' && p[1] == 'N' &&  p[2] == 'D' && !p[3])
    {
      recv_type = LINE_END;
      p += 3;
    }
  else
    die_1 ("invalid line type (%.5s)", p);

  return p;
}
