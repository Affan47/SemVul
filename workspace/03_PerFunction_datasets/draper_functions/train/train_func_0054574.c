zx_len_xmlns_if_not_seen(struct zx_ctx* c, struct zx_ns_s* ns, struct zx_ns_s** pop_seenp)
{
  if (!ns) {
    DD("no ns %p", ns);
    return 0;
  }
  if (!zx_push_seen(c, ns->prefix_len, ns->prefix, ns->url_len, ns->url, pop_seenp)) {
    DD("no push seen %p", ns);
    return 0;
  }

  if ((!ns->prefix || !*ns->prefix)
      && !memcmp(ns->url, zx_unknown_prefix, sizeof(zx_unknown_prefix)-1)) {
    DD("undeclared empty prefix %p", ns);
    return 0;
  }
  DD("add xmlns %p", ns);
  return sizeof(" xmlns")-1
    + (ns->prefix_len ? ns->prefix_len+1 : 0) + 2 + ns->url_len + 1;
}
