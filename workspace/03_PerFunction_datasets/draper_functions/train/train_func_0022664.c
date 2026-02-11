match_cert_name(char* req_host, char* host) {

  if (!host) return 0;


  if (host[0] == '*' && host[1] == '.') {
    host++;

    if (strlen(req_host) > strlen(host)) {


      while(req_host && req_host[0] != '.')
        req_host++;
    }
  }


  if (host) DEBUG("Comparing: %s %s\n", host, req_host);

  if (!host || strcasecmp(host, req_host))
    return 0;

  return 1;
}
