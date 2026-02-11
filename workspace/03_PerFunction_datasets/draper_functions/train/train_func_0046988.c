b00t_init(g, cmd, argc, argv)
  l1sp_ctx *g;
  char *cmd, *argv[];
{
  L1SP_PROT1_DECL(g);
  l1sp *r;
  char *a;

  r=g->l1_nil;
  l1sp_prot1(g, r);
  while(a=*argv++) {
    r=l1sp_cons(g, l1sp_intern0(g, a), r);
  }
  l1sp_unprot1(g);

  l1sp_def0(g, "argv", l1sp_nreverse(g->l1_nil, r));

  l1sp_defproc0(g, "split",   b00t_split);
  l1sp_defproc0(g, "repl",    b00t_repl);
  l1sp_defproc0(g, "read1",   b00t_read1);
  l1sp_defproc0(g, "objname", b00t_objname);
  l1sp_defproc0(g, "exist",   b00t_exist);
  l1sp_defprocn(g, "exec",    b00t_exec);
  l1sp_defproc0(g, "dirname", b00t_dirname);

  l1sp_load(g, l1sp_cat0(g, B00T, "/init.l1", (char*)0, (char*)0));
  l1sp_load(g, l1sp_cat0(g, B00T, "/", cmd, ".l1"));
}
