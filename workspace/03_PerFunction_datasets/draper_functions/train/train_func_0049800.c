funcargs (LexState *ls, expdesc *f) {
  FuncState *fs = ls->fs;
  expdesc args;
  int base, nparams;
  int line = ls->linenumber;
  switch (ls->t.token) {
    case '(': {
      if (line != ls->lastline)
        luaX_syntaxerror(ls,"ambiguous syntax (function call x new statement)");
      next(ls);
      if (ls->t.token == ')')
        args.k = VVOID;
      else {
        explist1(ls, &args);
        luaK_setcallreturns(fs, &args, LUA_MULTRET);
      }
      check_match(ls, ')', '(', line);
      break;
    }
    case '{': {
      constructor(ls, &args);
      break;
    }
    case TK_STRING: {
      codestring(ls, &args, ls->t.seminfo.ts);
      next(ls);
      break;
    }
    default: {
      luaX_syntaxerror(ls, "function arguments expected");
      return;
    }
  }
  lua_assert(f->k == VNONRELOC);
  base = f->info;
  if (args.k == VCALL)
    nparams = LUA_MULTRET;
  else {
    if (args.k != VVOID)
      luaK_exp2nextreg(fs, &args);
    nparams = fs->freereg - (base+1);
  }
  init_exp(f, VCALL, luaK_codeABC(fs, OP_CALL, base, nparams+1, 2));
  luaK_fixline(fs, line);
  fs->freereg = base+1;

}
