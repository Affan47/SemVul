globus_rls_client_lrc_attr_create(globus_rls_handle_t *h, char *name,
		globus_rls_obj_type_t objtype, globus_rls_attr_type_t type)

{
  static char		*method = "lrc_attr_create";
  globus_result_t	r;
  BUFFER		b;
  char			obuf[BUFLEN];
  char			tbuf[BUFLEN];

  if ((r = checkhandle(h)) != GLOBUS_SUCCESS)
    return r;

  return rrpc_call(h, &b, method, 3, name, iarg(objtype, obuf),
		   iarg(type, tbuf));
}
