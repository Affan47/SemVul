funcparams (LexState *ls, int slf) {
  FuncState *fs = ls->fs;
  int nparams = 1;
  switch (ls->token) {
    case '(': {
      int line = ls->linenumber;
      listdesc e;
      next(ls);
      explist(ls, &e);
      check_match(ls, ')', '(', line);
      close_exp(ls, e.pc, 1);
      nparams = e.n;
      break;
    }

    case '{':
      constructor(ls);
      break;

    case STRING:
      code_string(ls, ls->seminfo.ts);
      next(ls);
      break;

    default:
      luaX_error(ls, "function arguments expected");
      break;
  }
  code_byte(fs, CALL);
  code_byte(fs, 0);
  code_byte(fs, (Byte)(nparams+slf));
  return fs->pc-1;
}
