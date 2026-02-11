suffixedexp (LexState *ls, expdesc *v) {


  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  primaryexp(ls, v);
  for (;;) {
    switch (ls->t.token) {
      case '.': {
        fieldsel(ls, v);
        break;
      }
      case '[': {
        expdesc key;
        luaK_exp2anyregup(fs, v);
        yindex(ls, &key);
        luaK_indexed(fs, v, &key);
        break;
      }
      case ':': {
        expdesc key;
        luaX_next(ls);
        checkname(ls, &key);
        luaK_self(fs, v, &key);
        funcargs(ls, v, line);
        break;
      }
      case '(': case TK_STRING: case '{': {
        luaK_exp2nextreg(fs, v);
        funcargs(ls, v, line);
        break;
      }
      default: return;
    }
  }
}
