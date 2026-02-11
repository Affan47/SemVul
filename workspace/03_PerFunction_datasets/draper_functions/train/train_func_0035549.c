posplus(struct cdb_make *c,uint32 len)
{
  uint32 newpos = c->pos + len;
  if (newpos < len) { errno = error_nomem; return -1; }
  c->pos = newpos;
  return 0;
}
