freereg (FuncState *fs, int reg) {
  if (reg >= fs->nactvar && reg < MAXSTACK) {
    fs->freereg--;
    lua_assert(reg == fs->freereg);
  }
}
