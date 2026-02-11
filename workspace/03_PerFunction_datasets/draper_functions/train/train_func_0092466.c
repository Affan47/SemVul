rfc959_accept_active_connection (gftp_request * request)
{
  int infd, ret;
  intptr_t passive_transfer;
  rfc959_parms * parms;
#ifdef HAVE_IPV6
  struct sockaddr_in6 cli_addr;
#else
  struct sockaddr_in cli_addr;
#endif
  socklen_t cli_addr_len;

  parms = request->protocol_data;

  g_return_val_if_fail (request != NULL, GFTP_EFATAL);
  g_return_val_if_fail (parms->data_connection > 0, GFTP_EFATAL);

  gftp_lookup_request_option (request, "passive_transfer", &passive_transfer);
  g_return_val_if_fail (!passive_transfer, GFTP_EFATAL);

  cli_addr_len = sizeof (cli_addr);

  if ((ret = gftp_fd_set_sockblocking (request, parms->data_connection, 0)) < 0)
    return (ret);

  if ((infd = accept (parms->data_connection, (struct sockaddr *) &cli_addr,
       &cli_addr_len)) == -1)
    {
      request->logging_function (gftp_logging_error, request,
                                _("Cannot accept connection from server: %s\n"),
                                g_strerror (errno));
      gftp_disconnect (request);
      return (GFTP_ERETRYABLE);
    }

  close (parms->data_connection);
  parms->data_connection = infd;

  if ((ret = gftp_fd_set_sockblocking (request, parms->data_connection, 1)) < 0)
    return (ret);

  return (0);
}
