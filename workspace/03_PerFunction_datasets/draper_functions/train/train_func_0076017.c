luaK_storevar (LexState *ls, const expdesc *var) {
  FuncState *fs = ls->fs;
  switch (var->k) {
    case VLOCAL:
      luaK_code1(fs, OP_SETLOCAL, var->u.index);
      break;
    case VGLOBAL:
      luaK_code1(fs, OP_SETGLOBAL, var->u.index);
      break;
    case VINDEXED:
      luaK_code2(fs, OP_SETTABLE, 3, 3);
      break;
    default:
      LUA_INTERNALERROR("invalid var kind to store");
  }
}
