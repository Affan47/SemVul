qos_get_remove_cookie(request_rec *r, const char *cookie_name) {
  const char *cookie_h = apr_table_get(r->headers_in, "cookie");
  if(cookie_h) {
    char *cn = apr_pstrcat(r->pool, cookie_name, "=", NULL);
    char *p = ap_strcasestr(cookie_h, cn);
    if(p) {
      char *sp = p;
      char *value = NULL;
      p[0] = '\0';
      sp--;
      while((sp > cookie_h) && (sp[0] == ' ')) {
        sp[0] = '\0';
        sp--;
      }
      p = &p[strlen(cn)];
      value = ap_getword(r->pool, (const char **)&p, ';');
      while(p && (p[0] == ' ')) p++;

      if(p && (strncasecmp(p, "$path=", strlen("$path=")) == 0)) {
        ap_getword(r->pool, (const char **)&p, ';');
      }

      if(p && p[0]) {
        if(cookie_h[0]) {
          if(p[0] == ' ') {
            cookie_h = apr_pstrcat(r->pool, cookie_h, p, NULL);
          } else {
            cookie_h = apr_pstrcat(r->pool, cookie_h, " ", p, NULL);
          }
        } else {
          cookie_h = apr_pstrcat(r->pool, p, NULL);
        }
      }
      if(strlen(cookie_h) == 0) {
        apr_table_unset(r->headers_in, "cookie");
      } else {
        if((strncasecmp(cookie_h, "$Version=", strlen("$Version=")) == 0) &&
           (strlen(cookie_h) <= strlen("$Version=X; "))) {

          apr_table_unset(r->headers_in, "cookie");
        } else {
          apr_table_set(r->headers_in, "cookie", cookie_h);
        }
      }
      return value;
    }
  }
  return NULL;
}
