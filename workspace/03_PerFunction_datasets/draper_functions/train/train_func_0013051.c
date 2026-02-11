code_args (LexState *ls, int nparams, int dots) {
  FuncState *fs = ls->fs;
  fs->nlocalvar += nparams;
  nparams = fs->nlocalvar;
  if (!dots) {
    fs->f->code[1] = nparams;
    deltastack(ls, nparams);
  }
  else {
    fs->f->code[1] = nparams+ZEROVARARG;
    deltastack(ls, nparams+1);
    add_localvar(ls, luaS_new("arg"));
  }
}
