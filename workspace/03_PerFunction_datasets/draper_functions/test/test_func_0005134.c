genCodePostorderProcDec(Absyn *node, Table *symtab, int r) {
  char *name = symToString(node->u.procDec.name);
  Entry *e = lookup(symtab, node->u.procDec.name);
  int outsize = e->u.procEntry.size_args_out;
  int framesize, oldfp, oldret;
  int noleaf = (outsize == LEAF_PROC)?0:1;

  if(noleaf) {
    framesize = e->u.procEntry.size_local_vars
                + 2*REF_BYTE_SIZE + outsize;
    oldfp  = e->u.procEntry.size_local_vars + REF_BYTE_SIZE;
  } else {
    framesize = e->u.procEntry.size_local_vars + REF_BYTE_SIZE;
    oldfp  = 0;
  }
  oldret = e->u.procEntry.size_local_vars + 2*REF_BYTE_SIZE;

  fprintf(file, "\n\t.export\t%s\n", name);
  fprintf(file, "%s:\n", name);
  fprintf(file, "\tsub\t$%d,$%d,%d\t\t; allocate frame\n", R_SP, R_SP, framesize);
  fprintf(file, "\tstw\t$%d,$%d,%d\t\t; save old frame pointer\n", R_FP, R_SP, oldfp);
  fprintf(file, "\tadd\t$%d,$%d,%d\t\t; setup new frame pointer\n", R_FP, R_SP, framesize);

  if(noleaf)
  fprintf(file, "\tstw\t$%d,$%d,%d\t\t; save return register\n", R_RET, R_FP, -oldret);

  genCodePostorder(node->u.procDec.body, e->u.procEntry.localTable, r);

  if(noleaf)
  fprintf(file, "\tldw\t$%d,$%d,%d\t\t; restore return register\n", R_RET, R_FP, -oldret);


  fprintf(file, "\tldw\t$%d,$%d,%d\t\t; restore old frame pointer\n", R_FP, R_SP, oldfp);
  fprintf(file, "\tadd\t$%d,$%d,%d\t\t; release frame\n", R_SP, R_SP, framesize);
  fprintf(file, "\tjr\t$%d\t\t\t; return\n", R_RET);
}
