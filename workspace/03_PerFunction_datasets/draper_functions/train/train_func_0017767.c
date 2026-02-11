luaK_deltastack (FuncState *fs, int delta) {
  fs->stacklevel += delta;
  if (fs->stacklevel > fs->f->maxstacksize) {
    if (fs->stacklevel > MAXSTACK)
      luaK_error(fs->ls, "function or expression too complex");
    fs->f->maxstacksize = fs->stacklevel;
  }
}
