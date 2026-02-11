connect_to_server(const char *username, const char *hostname, int port,
		      char *errbuf, int errbufsize)
{
  if (0 != get_server_address(hostname, port, errbuf, errbufsize)) {
    return -1;
  }

  if (0 != try_to_connect(username, errbuf, errbufsize)) {
    return -1;
  }

  return 0;
}
