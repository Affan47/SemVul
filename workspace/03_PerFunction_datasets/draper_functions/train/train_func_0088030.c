luaX_syntaxerror (LexState *ls, const char *msg) {
  const char *lasttoken;
  switch (ls->t.token) {
    case TK_NAME:
      lasttoken = getstr(ls->t.seminfo.ts);
      break;
    case TK_STRING:
    case TK_NUMBER:
      lasttoken = luaZ_buffer(ls->buff);
      break;
    default:
      lasttoken = luaX_token2str(ls, ls->t.token);
      break;
  }
  luaX_error(ls, msg, lasttoken);
}
