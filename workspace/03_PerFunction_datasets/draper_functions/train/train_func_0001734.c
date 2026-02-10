exp1 (LexState *ls) {
  vardesc v;
  exp0(ls, &v);
  lua_pushvar(ls, &v);
  if (is_in(ls->token, expfollow) < 0)
    luaX_error(ls, "ill-formed expression");
}
