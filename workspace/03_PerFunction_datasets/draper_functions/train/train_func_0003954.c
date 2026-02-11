zx_DEC_ATTR_di12_AuthenticateSessionContext(struct zx_ctx* c, struct zx_di12_AuthenticateSessionContext_s* x)
{
  switch (x->gg.attr->g.tok) {
    case zx_descriptionIDRefs_ATTR:  x->descriptionIDRefs = x->gg.attr; return 1;

  default: return 0;
  }
}
