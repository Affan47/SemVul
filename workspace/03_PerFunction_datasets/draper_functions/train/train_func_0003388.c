dns_lookup(char* hostname) {
  struct hostent* host;

  if((host = gethostbyname(hostname)) == NULL) {
    herror("gethostbyname");
    return REG_FAILURE;
  }

#ifdef REG_DEBUG
  fprintf(stderr, "STEER: DNS lookup: host: %s\n", host->h_name);
  fprintf(stderr, "               IP:   %s\n",
	  inet_ntoa(*((struct in_addr*) host->h_addr)));
#endif


  sprintf(hostname, "%s",
	  inet_ntoa(*((struct in_addr*) host->h_addr_list[0])));

  return REG_SUCCESS;
}
