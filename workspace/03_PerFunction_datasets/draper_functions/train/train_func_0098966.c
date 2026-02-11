flatten_token(Acs_token *token, Kwv *token_kwv, char **value,
			  unsigned int *valuelen)
{
  char *p;
  Credentials *cr;
  Kwv *kwv;

  if (token_kwv == NULL) {
	kwv = kwv_init(10);
	kwv->dup_mode = KWV_ALLOW_DUPS;

	kwv_add(kwv, "ISSUED_BY", token->issued_by);
	kwv_add(kwv, "URL_PATH", token->url_path);
	if (token->identity != NULL)
	  kwv_add(kwv, "IDENTITY", token->identity);
	for (cr = token->credentials; cr != NULL; cr = cr->next)
	  kwv_add(kwv, "CREDENTIALS", cr->unique);
	kwv_add(kwv, "EXPIRES", ds_xprintf("%lu", token->expires));
	kwv_add(kwv, "LIMIT", ds_xprintf("%ld", token->limit));
	if (token->attrs != NULL) {
	  if (token->attrs->constraint != NULL)
		kwv_add(kwv, "ATTR_CONSTRAINT", token->attrs->constraint);
	  if (token->attrs->permit_chaining != NULL)
		kwv_add(kwv, "ATTR_PERMIT_CHAINING", token->attrs->permit_chaining);
	  if (token->attrs->pass_credentials != NULL)
		kwv_add(kwv, "ATTR_PASS_CREDENTIALS", token->attrs->pass_credentials);
	  if (token->attrs->pass_http_cookie != NULL)
		kwv_add(kwv, "ATTR_PASS_HTTP_COOKIE", token->attrs->pass_http_cookie);
	}
	kwv_add(kwv, "UNIQUE", token->unique);
  }
  else
	kwv = token_kwv;

  p = kwv_str(kwv);
  *valuelen = strba64((unsigned char *) p, strlen(p) + 1, value);
}
