server_status(char *host, int port)
{
  PRNetAddr   *netaddr = NULL;
  PRStatus    err;
  PRFileDesc *req_socket= NULL;
  int retcode = 0;

  if (NULL == host) {
    return -1;
  }

  netaddr = (PRNetAddr *)calloc(1, sizeof(PRNetAddr));
  if (NULL == netaddr) {
    rpt_err(APP_ERROR, "Failed to allocate PRNetAddr", NULL, NULL);
    return -1;
  }
  err = PR_StringToNetAddr(host, netaddr);
  if (PR_SUCCESS == err) {
    PR_InitializeNetAddr(PR_IpAddrNull, (PRUint16)port, netaddr);
  } else {
    PRAddrInfo *infop = PR_GetAddrInfoByName(host,
                            PR_AF_UNSPEC, (PR_AI_ADDRCONFIG|PR_AI_NOCANONNAME));
    if (infop) {
      void *iter = NULL;
      memset( netaddr, 0, sizeof( PRNetAddr ));

      iter = PR_EnumerateAddrInfo(iter, infop, (PRUint16)port, netaddr);
      if (NULL == iter) {
         rpt_err(APP_ERROR, "Failed to enumerate addrinfo", NULL, NULL);
         retcode = -1;
      }
      PR_FreeAddrInfo(infop);
    } else {
      rpt_err(APP_ERROR, "Failed to get addrinfo", NULL, NULL);
      retcode = -1;
    }
  }

  if (retcode < 0) {
    free(netaddr);
    return retcode;
  } else {
    req_socket = PR_NewTCPSocket();
    err = PR_Connect(req_socket, netaddr, 10000);
    free(netaddr);
    if (PR_SUCCESS == err) {
      return 1;
    } else {
      return 0;
    }
  }
}
