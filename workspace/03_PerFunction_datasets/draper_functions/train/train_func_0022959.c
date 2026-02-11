zx_xmlns_detected(struct zx_ctx* c, struct zx_elem_s* x, const char* url)
{
  struct zx_ns_s* ns;
  const char* prefix;

  for (prefix = url-2; !ONE_OF_5(*prefix, ':', ' ', '\n', '\r', '\t'); --prefix) ;
  ++prefix;
  DD("xmlns detected(%.*s)", url-2-prefix, prefix);
  ns = ZX_ZALLOC(c, struct zx_ns_s);
  ns->url = url;
  ns->url_len = c->p - url;
  ns->prefix_len = url-2-prefix;
  ns->prefix = prefix;
  ns->n = x->xmlns;
  x->xmlns = ns;
  return ns;
}
