luaY_parser (lua_State *L, ZIO *z, Mbuffer *buff,
                      Dyndata *dyd, const char *name, int firstchar) {
  LexState lexstate;
  FuncState funcstate;
  Closure *cl = luaF_newLclosure(L, 1);

  setclLvalue(L, L->top, cl);
  incr_top(L);
  funcstate.f = cl->l.p = luaF_newproto(L);
  funcstate.f->source = luaS_new(L, name);
  lexstate.buff = buff;
  lexstate.dyd = dyd;
  dyd->actvar.n = dyd->gt.n = dyd->label.n = 0;
  luaX_setinput(L, &lexstate, z, funcstate.f->source, firstchar);
  mainfunc(&lexstate, &funcstate);
  lua_assert(!funcstate.prev && funcstate.nups == 1 && !lexstate.fs);

  lua_assert(dyd->actvar.n == 0 && dyd->gt.n == 0 && dyd->label.n == 0);
  return cl;
}
