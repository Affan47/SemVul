luaK_number (FuncState *fs, Number f) {
  if (f <= (Number)MAXARG_S && (Number)(int)f == f)
    luaK_code1(fs, OP_PUSHINT, (int)f);
  else
    luaK_code1(fs, OP_PUSHNUM, number_constant(fs, f));
}
