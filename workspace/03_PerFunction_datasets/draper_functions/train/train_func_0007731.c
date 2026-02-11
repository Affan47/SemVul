markroot (lua_State *L) {
  global_State *g = G(L);
  g->gray = NULL;
  g->grayagain = NULL;
  g->weak = NULL;
  markobject(g, g->mainthread);

  markvalue(g, gt(g->mainthread));
  markvalue(g, registry(L));
  markmt(g);
  g->gcstate = GCSpropagate;
}
