fscope_uvmark(FuncState *fs, BCReg level)
{
  FuncScope *bl;
  for (bl = fs->bl; bl && bl->nactvar > level; bl = bl->prev)
    ;
  if (bl)
    bl->flags |= FSCOPE_UPVAL;
}
