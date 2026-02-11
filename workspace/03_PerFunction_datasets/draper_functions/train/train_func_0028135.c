l1sp_load0(g, f)
  l1sp_ctx *g;
  char *f;
{
  L1SP_PROT1_DECL(g);
  int saved_errno=errno;
  char b[L1SP_IOBUFFER];
  l1sp *l;
  int fd;

  fd=l1sp_openread0(f);
  if(-1==fd) return g->l1_nil;

  l=g->l1_nil;
  l1sp_prot1(g, l);

  l1sp_setbuf_r(g,
                f,
                fd,
                &b[(size_t)0U],
                sizeof b/sizeof b[(size_t)0U]);
  l=l1sp_rdsexp(g);

  l1sp_setbuf_w(g,
                "/dev/fd/1",
                1,
                &b[(size_t)0U],
                sizeof b/sizeof b[(size_t)0U]);
  for(; l1sp_consp(l); l=l1sp_cdr(l)) l1sp_eval(g, l1sp_car(l));

  l1sp_unprot1(g);
  l1sp_close(fd);
  errno=saved_errno;
  return g->l1_t;
}
