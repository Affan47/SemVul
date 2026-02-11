gftp_fd_write (gftp_request * request, const char *ptr, size_t size, int fd)
{
  intptr_t network_timeout;
  struct timeval tv;
  int ret, s_ret;
  ssize_t w_ret;
  fd_set fset;

  g_return_val_if_fail (fd >= 0, GFTP_EFATAL);

  gftp_lookup_request_option (request, "network_timeout", &network_timeout);

  errno = 0;
  ret = 0;
  FD_ZERO (&fset);

  do
    {
      FD_SET (fd, &fset);
      tv.tv_sec = network_timeout;
      tv.tv_usec = 0;
      s_ret = select (fd + 1, NULL, &fset, NULL, &tv);
      if (s_ret == -1 && (errno == EINTR || errno == EAGAIN))
        {
          if (request != NULL && request->cancel)
            {
              gftp_disconnect (request);
              return (GFTP_ERETRYABLE);
            }

          continue;
        }
      else if (s_ret <= 0)
        {
          if (request != NULL)
            {
              request->logging_function (gftp_logging_error, request,
                                         _("Connection to %s timed out\n"),
                                         request->hostname);
              gftp_disconnect (request);
            }

          return (GFTP_ERETRYABLE);
        }

      w_ret = write (fd, ptr, size);
      if (w_ret < 0)
        {
          if (errno == EINTR || errno == EAGAIN)
            {
              if (request != NULL && request->cancel)
                {
                  gftp_disconnect (request);
                  return (GFTP_ERETRYABLE);
                }

              continue;
             }

          if (request != NULL)
            {
              request->logging_function (gftp_logging_error, request,
                                    _("Error: Could not write to socket: %s\n"),
                                    g_strerror (errno));
              gftp_disconnect (request);
            }

          return (GFTP_ERETRYABLE);
        }

      ptr += w_ret;
      size -= w_ret;
      ret += w_ret;
    }
  while (size > 0);

  return (ret);
}
