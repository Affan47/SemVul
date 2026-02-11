dacs_check_authorization(request_rec *r, const char *require_line,
						 const void *parsed_require_line)
{
  int st;
#ifdef NOTDEF

  apr_ipsubnet_t **ip = (apr_ipsubnet_t **)parsed_require_line;

  while (*ip) {
	if (apr_ipsubnet_test(*ip, r->useragent_addr))
	  return AUTHZ_GRANTED;
	ip++;
  }


  return(AUTHZ_DENIED);
#endif

  st = dacs_check_auth(r);

#ifdef APACHE_2_4_OR_NEWER
  if (st == HTTP_PROXY_AUTHENTICATION_REQUIRED) {
	r->status = st;
	r->user = "";
	return(AUTHZ_DENIED_NO_USER);
  }
#endif

  if (st == HTTP_OK || st == OK)
	return(AUTHZ_GRANTED);

  return(AUTHZ_DENIED);
}
