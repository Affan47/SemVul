zxid_free_at(struct zxid_conf *cf, struct zxid_attr *attr)
{
  while (attr) {
    struct zxid_attr *next = attr->n;
    ZX_FREE(cf->ctx, attr->name);
    if (attr->val) ZX_FREE(cf->ctx, attr->val);
    ZX_FREE(cf->ctx, attr);
    attr = next;
  }
}
