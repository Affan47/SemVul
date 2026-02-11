svcraw_getargs (SVCXPRT *xprt, xdrproc_t xdr_args, caddr_t args_ptr)
{
  struct svcraw_private_s *srp = svcraw_private;

  if (srp == 0)
    return FALSE;
  return (*xdr_args) (&srp->xdr_stream, args_ptr);
}
