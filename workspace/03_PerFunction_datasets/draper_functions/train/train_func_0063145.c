resolve_dns_servers() {
  struct addrinfo hints;
  struct addrinfo *addr_ip;
  char* token;
  int r;
  int i = 0;
  char *pch = strchr(dns_servers, ',');
  int has_chn_dns = 0;
  int has_foreign_dns = 0;
  dns_servers_len = 1;
  while (pch != NULL) {
    dns_servers_len++;
    pch = strchr(pch + 1, ',');
  }
  dns_server_addrs = calloc(dns_servers_len, sizeof(id_addr_t));

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  token = strtok(dns_servers, ",");
  while (token) {
    char *port;
    memset(global_buf, 0, BUF_SIZE);
    strncpy(global_buf, token, BUF_SIZE - 1);
    port = (strrchr(global_buf, ':'));
    if (port) {
      *port = '\0';
      port++;
    } else {
      port = "53";
    }
    if (0 != (r = getaddrinfo(global_buf, port, &hints, &addr_ip))) {
      VERR("%s:%s\n", gai_strerror(r), token);
      return -1;
    }
    dns_server_addrs[i].addr = addr_ip->ai_addr;
    dns_server_addrs[i].addrlen = addr_ip->ai_addrlen;
    i++;
    token = strtok(0, ",");
    if (test_ip_in_list(((struct sockaddr_in *)addr_ip->ai_addr)->sin_addr,
                        &chnroute_list)) {
      has_chn_dns = 1;
    } else {
      has_foreign_dns = 1;
    }
  }
  if (chnroute_file) {
    if (!(has_chn_dns && has_foreign_dns)) {
      VERR("You should have at least one Chinese DNS and one foreign DNS when "
          "chnroutes is enabled\n");
      return 0;
    }
  }
  return 0;
}
