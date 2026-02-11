backendCheckSideChannel(
    int         snmp_fd,
    http_addr_t *addr)
{
  fd_set	input;
  struct timeval timeout;


  FD_ZERO(&input);
  FD_SET(CUPS_SC_FD, &input);

  timeout.tv_sec = timeout.tv_usec = 0;

  if (select(CUPS_SC_FD + 1, &input, NULL, NULL, &timeout) > 0)
    backendNetworkSideCB(-1, -1, snmp_fd, addr, 0);
}
