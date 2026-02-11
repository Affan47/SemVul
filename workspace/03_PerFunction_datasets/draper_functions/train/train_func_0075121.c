csp_qstring(vbuf *vb, const char *dp, int len) {
  unsigned char ch;
  char buf[10];
  int cn;

  CSP_ADDSTR("\"");
  for (cn=0; cn<len; cn++) {
    ch= *dp++;
    if (ch == '\\') {
      CSP_ADDSTR("\\\\");
    } else if (ch == '"') {
      CSP_ADDSTR("\\\"");
    } else if (ch >= 32 && ch <= 126) {
      if (!adns__vbuf_append(vb,&ch,1)) R_NOMEM;
    } else {
      sprintf(buf,"\\x%02x",ch);
      CSP_ADDSTR(buf);
    }
  }
  CSP_ADDSTR("\"");

  return adns_s_ok;
}
