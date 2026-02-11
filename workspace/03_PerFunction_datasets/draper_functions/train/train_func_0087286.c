zx_xmlns_decl(struct zx_ctx* c, int prefix_len, const char* prefix, int url_len, const char* url)
{
  struct zx_ns_s* alias;
  struct zx_ns_s* new_ns;
  struct zx_ns_s* ns;

  ns = zx_locate_ns_by_url(c, url_len, url);
  if (!ns) {
    D("Namespace(%.*s) not found by URL(%.*s) (probably unknown or wrong namespace URL)", prefix_len, prefix, url_len, url);
    zx_xml_parse_dbg(c, '-', __FUNCTION__, "Namespace here");
    ns = zx_locate_ns_by_prefix(c, prefix_len, prefix);
    if (!ns) {

      D("Namespace not found by prefix(%.*s) or URL(%.*s) (probably unknown or wrong namespace URL)", prefix_len, prefix, url_len, url);
      new_ns = zx_new_unknown_ns(c, prefix_len, prefix, url_len, url);
      new_ns->n = c->unknown_ns;
      c->unknown_ns = new_ns;
      return new_ns;
    }
  }

  new_ns = zx_new_known_ns(c, prefix_len, prefix, ns);


  if (ns->prefix_len == prefix_len && (!prefix_len || !memcmp(ns->prefix, prefix, prefix_len)))
    goto known_prefix;
  for (alias = ns->n; alias; alias = alias->n)
    if (alias->prefix_len == prefix_len && (!prefix_len || !memcmp(alias->prefix, prefix, prefix_len)))
      goto known_prefix;

  D("New prefix(%.*s) known URL(%.*s)", prefix_len, prefix, url_len, url);
  ns->n = new_ns->n;
  new_ns->n = ns;
known_prefix:
  return new_ns;
}
