pmap_rmtcall (struct sockaddr_in *addr,
				    const unsigned long prog,
				    const unsigned long vers,
				    const unsigned long proc,
				    xdrproc_t xdrargs,
				    char* argsp, xdrproc_t xdrres,
				    char* resp, struct timeval tout,
				    unsigned long *port_ptr) {
  int socket = -1;
  register CLIENT *client;
  struct rmtcallargs a;
  struct rmtcallres r;
  enum clnt_stat stat;

  addr->sin_port = htons((short)PMAPPORT);
  client = clntudp_create(addr, PMAPPROG, PMAPVERS, timeout, &socket);
  if (client != (CLIENT *) NULL) {
    a.prog = prog;
    a.vers = vers;
    a.proc = proc;
    a.args_ptr = argsp;
    a.xdr_args = xdrargs;
    r.port_ptr = port_ptr;
    r.results_ptr = resp;
    r.xdr_results = xdrres;
    stat = CLNT_CALL(client, PMAPPROC_CALLIT, (xdrproc_t)xdr_rmtcall_args, (char*)&a,
		      (xdrproc_t)xdr_rmtcallres, (char*)&r, tout);
    CLNT_DESTROY(client);
  } else {
    stat = RPC_FAILED;
  }
  (void) close(socket);
  addr->sin_port = 0;
  return (stat);
}
