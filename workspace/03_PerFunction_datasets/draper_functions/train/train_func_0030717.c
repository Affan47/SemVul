key_setnet (struct key_netstarg *arg)
{
  keystatus status;

  if (!key_call ((u_long) KEY_NET_PUT, (xdrproc_t) xdr_key_netstarg,
		 (char *) arg,(xdrproc_t) xdr_keystatus,
		 (char *) &status))
    return -1;

  if (status != KEY_SUCCESS)
    {
      debug ("key_setnet status is nonzero");
      return -1;
    }
  return 1;
}
