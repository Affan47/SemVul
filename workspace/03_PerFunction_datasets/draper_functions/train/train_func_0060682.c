__ypclnt_call (const char *domain, u_long prog, xdrproc_t xargs,
	       caddr_t req, xdrproc_t xres, caddr_t resp, dom_binding **ydb,
	       int print_error)
{
  enum clnt_stat result;

  result = clnt_call ((*ydb)->dom_client, prog,
		      xargs, req, xres, resp, RPCTIMEOUT);

  if (result != RPC_SUCCESS)
    {


      if (print_error)
	clnt_perror ((*ydb)->dom_client, "do_ypcall: clnt_call");

      return YPERR_RPC;
    }

  return YPERR_SUCCESS;
}
