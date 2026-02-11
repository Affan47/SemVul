clntraw_create (u_long prog, u_long vers)
{
  struct clntraw_private_s *clp = clntraw_private;
  struct rpc_msg call_msg;
  XDR *xdrs;
  CLIENT *client;

  if (clp == 0)
    {
      clp = (struct clntraw_private_s *) calloc (1, sizeof (*clp));
      if (clp == 0)
	return (0);
      clntraw_private = clp;
    }
  xdrs = &clp->xdr_stream;
  client = &clp->client_object;


  call_msg.rm_direction = CALL;
  call_msg.rm_call.cb_rpcvers = RPC_MSG_VERSION;
  call_msg.rm_call.cb_prog = prog;
  call_msg.rm_call.cb_vers = vers;
  xdrmem_create (xdrs, clp->mashl_callmsg.msg, MCALL_MSG_SIZE, XDR_ENCODE);
  if (!xdr_callhdr (xdrs, &call_msg))
    {
      perror (_ ("clnt_raw.c: fatal header serialization error"));
    }
  clp->mcnt = XDR_GETPOS (xdrs);
  XDR_DESTROY (xdrs);


  xdrmem_create (xdrs, clp->_raw_buf, UDPMSGSIZE, XDR_FREE);


  client->cl_ops = (struct clnt_ops *) &client_ops;
  client->cl_auth = authnone_create ();
  return client;
}
