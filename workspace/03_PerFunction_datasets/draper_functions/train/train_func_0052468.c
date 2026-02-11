adjustlocalvars (LexState *ls, int nvars) {
  FuncState *fs = ls->fs;
  while (nvars--)
    fs->f->locvars[fs->actloc[fs->nactloc++]].startpc = fs->pc;
}
