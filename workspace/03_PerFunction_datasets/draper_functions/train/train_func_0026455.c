luaK_adjuststack (FuncState *fs, int n) {
  if (n > 0)
    luaK_code1(fs, OP_POP, n);
  else
    luaK_code1(fs, OP_PUSHNIL, -n);
}
