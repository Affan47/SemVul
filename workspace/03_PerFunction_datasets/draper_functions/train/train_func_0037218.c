parse_eport(char* str, globus_ftp_control_host_port_t* host_port) {
  memset(host_port,0,sizeof(globus_ftp_control_host_port_t));
  for(;isblank(*str);++str) { };
  if((*str < 33) || (*str > 126)) return -1;
  char delim = *str;
  const char* protocol_s = ++str;
  for(;*str != delim;++str) { if(!*str) return -1; };
  *str = 0;
  const char* addr_s = ++str;
  for(;*str != delim;++str) { if(!*str) return -1; };
  *str = 0;
  const char* port_s = ++str;
  for(;*str != delim;++str) { if(!*str) return -1; };
  *str = 0;
  char* port_e = NULL;
  unsigned short port = strtoul(port_s,&port_e,10);
  if(!port) return -1;
  host_port->port = port;
  char* protocol_e = NULL;
  unsigned short protocol = strtoul(protocol_s,&protocol_e,10);
  if(protocol == 1) {
    struct in_addr addr;
    if(inet_pton(AF_INET,addr_s,&addr) != 1) return -1;
    if(sizeof(addr) > sizeof(host_port->host)) return -1;
    memcpy(&(host_port->host),&addr,sizeof(addr));
    host_port->hostlen = sizeof(addr);
  } else if(protocol == 2) {
    struct in6_addr addr;
    if(inet_pton(AF_INET6,addr_s,&addr) != 1) return -1;
    if(sizeof(addr) > sizeof(host_port->host)) return -1;
    memcpy(&(host_port->host),&addr,sizeof(addr));
    host_port->hostlen = sizeof(addr);
  } else {
    return -1;
  };
  return 0;
}
