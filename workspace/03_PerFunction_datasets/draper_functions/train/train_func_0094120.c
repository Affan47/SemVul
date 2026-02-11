create_connected_socket(char *hostname,int port,int mode) {
  PRAddrInfo *addr_info;
  void *addr_iter;
  PRNetAddr addr;
  PRFileDesc *localsocket;
  int can_exit,valid_socket;
  PRUint16 af_spec;

  localsocket=NULL;

  addr_info=NULL;

  af_spec=PR_AF_UNSPEC;

  if (!(mode&MODE_IP6MODE)) af_spec=PR_AF_INET;

  addr_info=PR_GetAddrInfoByName(hostname,af_spec,PR_AI_ADDRCONFIG);

  if (addr_info == NULL) {
    print_nspr_error();
    return NULL;
  }


  addr_iter=NULL;
  can_exit=0;
  valid_socket=0;

  while (!can_exit) {
    addr_iter=PR_EnumerateAddrInfo(addr_iter,addr_info,port,&addr);

    if (addr_iter==NULL) {
      can_exit=1;
    } else {
      if ((PR_NetAddrFamily(&addr)==PR_AF_INET && (mode&MODE_IP4MODE)) ||
          (PR_NetAddrFamily(&addr)==PR_AF_INET6 && (mode&MODE_IP6MODE))) {


        localsocket=create_socket(!(mode&MODE_NO_SSL),(PR_NetAddrFamily(&addr)==PR_AF_INET6));

        if (localsocket) {

          if (PR_Connect(localsocket,&addr,PR_INTERVAL_NO_TIMEOUT)==PR_SUCCESS) {

            if ((!(mode&MODE_NO_SSL)) && SSL_ForceHandshake(localsocket)!=SECSuccess) {

              print_nspr_error();
              if (PR_Close(localsocket)!=PR_SUCCESS) {
                print_nspr_error();
                can_exit=1;
              }
              localsocket=NULL;
            }


            can_exit=1;
          } else {

            if (PR_Close(localsocket)!=PR_SUCCESS) {
              print_nspr_error();
              can_exit=1;
            }
            localsocket=NULL;
          }
        }
      }
    }
  }

  if (!localsocket) {

    fprintf(stderr,"Can't connect to host %s on port %d!\n",hostname,port);
  }

  PR_FreeAddrInfo(addr_info);

  return localsocket;
}
