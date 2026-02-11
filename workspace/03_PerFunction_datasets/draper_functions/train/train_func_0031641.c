zxid_get_sid_from_cookie(zxid_conf* cf, zxid_cgi* cgi, const char* cookie)
{
  char* q;
  int len;
  if (!cookie)
    return;
  len = strlen(cf->ses_cookie_name);
  for (cookie = strstr(cookie, cf->ses_cookie_name);
       cookie;
       cookie = strstr(cookie + 1, cf->ses_cookie_name))
    if (cookie[len] == '=') {
      cookie += len + 1;
      if (*cookie == '"')
	++cookie;
      q = strchr(cookie, ';');
      len = q ? (q-cookie) : strlen(cookie);
      if (cookie[len-1] == '"')
	--len;
      cgi->sid = ZX_ALLOC(cf->ctx, len + 1);
      memcpy(cgi->sid, cookie, len);
      cgi->sid[len] = 0;
      return;
    }
}
