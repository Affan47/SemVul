globus_rls_client_rli_rli_list(globus_rls_handle_t *h,
			       globus_list_t **rliinfo_list)

{
  static char		*method = "rli_rli_list";
  globus_result_t	r;
  BUFFER		b;
  RLSLIST		*rlslist;
  int			nomem;
  char			url[MAXURL];
  char			uibuf[100];
  char			fbuf[100];
  char			lubuf[100];
  globus_rls_rli_info_t	*rliinfo;

  if ((r = checkhandle(h)) != GLOBUS_SUCCESS)
    return r;

  if ((r = rrpc_call(h, &b, method, 0)) != GLOBUS_SUCCESS)
    return r;

  if ((rlslist = rlslist_new(globus_libc_free)) == NULL)
    nomem = 1;
  else
    nomem = 0;
  while (1) {
    if ((r = rrpc_getstr(h, &b, url, BUFLEN)) != GLOBUS_SUCCESS)
      return r;
    if (!*url)
      break;
    if ((r = rrpc_getstr(h, &b, uibuf, BUFLEN)) != GLOBUS_SUCCESS)
      return r;
    if ((r = rrpc_getstr(h, &b, fbuf, BUFLEN)) != GLOBUS_SUCCESS)
      return r;
    if ((r = rrpc_getstr(h, &b, lubuf, BUFLEN)) != GLOBUS_SUCCESS)
      return r;

    if (!(rliinfo = globus_libc_malloc(sizeof(*rliinfo)))) {
      nomem++;
      continue;
    }
    strcpy(rliinfo->url, url);
    rliinfo->updateinterval = atoi(uibuf);
    rliinfo->flags = atoi(fbuf);
    rliinfo->lastupdate = atoi(lubuf);

    if (globus_list_insert(&rlslist->list, rliinfo) != GLOBUS_SUCCESS) {
      globus_libc_free(rliinfo);
      nomem++;
      continue;
    }
  }
  if (nomem && rlslist)
    globus_rls_client_free_list(rlslist->list);
  else
    *rliinfo_list = rlslist->list;

  if (nomem)
    return mkresult(GLOBUS_RLS_NOMEMORY, NULL);
  return GLOBUS_SUCCESS;
}
