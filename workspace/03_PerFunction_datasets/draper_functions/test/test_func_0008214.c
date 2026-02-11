get_client_encoding(request_rec *r,
		    apr_array_header_t *encmap, const char *lookup) {
  void         **list = (void **)encmap->elts;
  apr_array_header_t  *encs = apr_array_make(r->pool, 1, sizeof(char *));

  int i;


  *((char **)apr_array_push(encs)) = apr_pstrdup(r->pool, "UTF-8");

  if (! lookup)
    return encs;


  for (i = 0 ; i < encmap->nelts ; i += 2) {
    if (ap_regexec((regex_t *)list[i], lookup, 0, NULL, 0) == 0) {
      apr_array_cat(encs, (apr_array_header_t *)list[i + 1]);
      return encs;
    }
  }

  return encs;
}
