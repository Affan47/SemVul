zx_enc_seen(char* p, struct zx_ns_s* ns)
{
  for (; ns; ns = ns->seen_pop) {

    if ((!ns->prefix || !*ns->prefix)
	&& !memcmp(ns->url, zx_unknown_prefix, sizeof(zx_unknown_prefix)-1))
      continue;
    ZX_OUT_MEM(p, " xmlns", sizeof(" xmlns")-1);
    if (ns->prefix_len) {
      ZX_OUT_CH(p, ':');
      ZX_OUT_MEM(p, ns->prefix, ns->prefix_len);
    }
    ZX_OUT_CH(p, '=');
    ZX_OUT_CH(p, '"');
    ZX_OUT_MEM(p, ns->url, ns->url_len);
    ZX_OUT_CH(p, '"');
  }
  return p;
}
