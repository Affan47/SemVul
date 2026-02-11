mkresult(int rc, char *specific)

{
  globus_object_t	*o;
  char			errmsg[MAXERRMSG];

  if (rc == GLOBUS_RLS_SUCCESS)
    return GLOBUS_SUCCESS;
  o = globus_error_construct_error(GLOBUS_RLS_CLIENT_MODULE, NULL, rc,
#ifndef GLOBUS_ERROR_CONSTRUCT_ERROR_FIVE_ARGS
	NULL, NULL, 0,
#endif
        "%s", globus_rls_errmsg(rc, specific, errmsg, MAXERRMSG));
  return globus_error_put(o);
}
