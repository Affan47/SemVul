luaX_token2str (LexState *ls, int token) {
  if (token < FIRST_RESERVED) {
    lua_assert(token == cast_uchar(token));
    return luaO_pushfstring(ls->L, "'%c'", token);
  }
  else {
    const char *s = luaX_tokens[token - FIRST_RESERVED];
    if (token < TK_EOS)
      return luaO_pushfstring(ls->L, "'%s'", s);
    else
      return s;
  }
}
