constructor (LexState *ls, expdesc *t) {

  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  int pc = luaK_codeABC(fs, OP_NEWTABLE, 0, 0, 0);
  struct ConsControl cc;
  cc.na = cc.nh = cc.tostore = 0;
  cc.t = t;
  init_exp(t, VRELOCABLE, pc);
  init_exp(&cc.v, VVOID, 0);
  luaK_exp2nextreg(ls->fs, t);
  check(ls, '{');
  do {
    lua_assert(cc.v.k == VVOID || cc.tostore > 0);
    testnext(ls, ';');
    if (ls->t.token == '}') break;
    closelistfield(fs, &cc);
    switch(ls->t.token) {
      case TK_NAME: {
        lookahead(ls);
        if (ls->lookahead.token != '=')
          listfield(ls, &cc);
        else
          recfield(ls, &cc);
        break;
      }
      case '[': {
        recfield(ls, &cc);
        break;
      }
      default: {
        listfield(ls, &cc);
        break;
      }
    }
  } while (testnext(ls, ',') || testnext(ls, ';'));
  check_match(ls, '}', '{', line);
  lastlistfield(fs, &cc);
  SETARG_B(fs->f->code[pc], luaO_int2fb(cc.na));
  SETARG_C(fs->f->code[pc], luaO_log2(cc.nh)+1);
}
