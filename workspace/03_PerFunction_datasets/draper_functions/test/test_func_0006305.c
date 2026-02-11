luaF_close (lua_State *L, StkId level) {
  UpVal *uv;
  global_State *g = G(L);
  while (L->openupval != NULL && (uv = gco2uv(L->openupval))->v >= level) {
    GCObject *o = obj2gco(uv);
    lua_assert(!isblack(o) && uv->v != &uv->u.value);
    L->openupval = uv->next;
    if (isdead(g, o))
      luaF_freeupval(L, uv);
    else {
      unlinkupval(uv);
      setobj(L, &uv->u.value, uv->v);
      uv->v = &uv->u.value;
      gch(o)->next = g->allgc;
      g->allgc = o;
      luaC_checkupvalcolor(g, uv);
    }
  }
}
