retstat (LexState *ls) {

  FuncState *fs = ls->fs;
  next(ls);
  if (!block_follow(ls->t.token))
    explist1(ls);
  luaK_code1(fs, OP_RETURN, ls->fs->nactloc);
  fs->stacklevel = fs->nactloc;
}
