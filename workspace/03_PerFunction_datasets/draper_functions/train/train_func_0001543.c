globus_rls_client_lrc_attr_value_get(globus_rls_handle_t *h, char *key,
			char *name, globus_rls_obj_type_t objtype,
			globus_list_t **attr_list)

{
  static char			*method = "lrc_attr_value_get";
  globus_result_t		r;
  globus_result_t		saver;
  BUFFER			b;
  char				obuf[100];
  char				nbuf[BUFLEN];
  char				tbuf[BUFLEN];
  char				sval[BUFLEN];
  globus_rls_attribute_t	*attr;
  int				nomem;
  RLSLIST			*rlslist;

  if ((r = checkhandle(h)) != GLOBUS_SUCCESS)
    return r;

  if ((r = rrpc_call(h, &b, method, 3, key, name,
		     iarg(objtype, obuf))) != GLOBUS_SUCCESS)
    return r;

  saver = GLOBUS_SUCCESS;
  if ((rlslist = rlslist_new(free_attr)) == NULL)
    nomem = 1;
  else
    nomem = 0;
  while (1) {
    if ((r = rrpc_getstr(h, &b, nbuf, BUFLEN)) != GLOBUS_SUCCESS)
      return r;
    if (!*nbuf)
      break;
    if ((r = rrpc_getstr(h, &b, tbuf, BUFLEN)) != GLOBUS_SUCCESS)
      return r;
    if ((r = rrpc_getstr(h, &b, sval, BUFLEN)) != GLOBUS_SUCCESS)
      return r;

    if (!(attr = globus_libc_calloc(1, sizeof(*attr)))) {
      nomem++;
      continue;
    }
    if ((attr->name = globus_libc_strdup(nbuf)) == NULL) {
      free_attr(attr);
      nomem++;
      continue;
    }
    if ((r = globus_rls_client_s2attr(atoi(tbuf), sval,
				      attr)) != GLOBUS_RLS_SUCCESS) {
      saver = r;
      free_attr(attr);
      continue;
    }
    attr->objtype = objtype;
    if (globus_list_insert(&rlslist->list, attr) != GLOBUS_SUCCESS) {
      free_attr(attr);
      nomem++;
      continue;
    }

  }
  if (nomem && rlslist)
    globus_rls_client_free_list(rlslist->list);
  else
    *attr_list = rlslist->list;

  if (nomem)
    return mkresult(GLOBUS_RLS_NOMEMORY, NULL);
  return saver;
}
