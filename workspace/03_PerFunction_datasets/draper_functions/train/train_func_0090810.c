ipmipower_poll (struct pollfd *ufds, unsigned int nfds, int timeout)
{
  int n;
  struct timeval tv, tv_orig;
  struct timeval start, end, delta;


  if (timeout >= 0)
    {

      tv_orig.tv_sec = (long)timeout/1000;
      tv_orig.tv_usec = (timeout % 1000) * 1000;

      if (gettimeofday(&start, NULL) < 0)
        {
          IPMIPOWER_ERROR (("gettimeofday: %s", strerror (errno)));
          exit (1);
        }
    }
  else
    {
      tv_orig.tv_sec = 0;
      tv_orig.tv_usec = 0;
    }


  do
    {
      n = poll(ufds, nfds, timeout);


      if (n < 0 && errno != EINTR)
        {
          IPMIPOWER_ERROR (("poll: %s", strerror (errno)));
          exit (1);
        }

      if (n < 0 && timeout >= 0)
        {
          if (gettimeofday(&end, NULL) < 0)
            {
              IPMIPOWER_ERROR (("gettimeofday: %s", strerror (errno)));
              exit (1);
            }

          timersub(&end, &start, &delta);
          timersub(&tv_orig, &delta, &tv);
          timeout = (tv.tv_sec * 1000) + (tv.tv_usec/1000);
        }
    } while (n < 0);

  return n;
}
