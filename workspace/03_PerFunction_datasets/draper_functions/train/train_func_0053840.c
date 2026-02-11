csp_domain(vbuf *vb, const char *domain) {
  CSP_ADDSTR(domain);
  if (!*domain) CSP_ADDSTR(".");
  return adns_s_ok;
}
