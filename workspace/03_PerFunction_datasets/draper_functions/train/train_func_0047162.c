read_string (LexState *LS, int del, SemInfo *seminfo) {
  lua_State *L = LS->L;
  size_t l = 0;
  checkbuffer(L, 10, l);
  save_and_next(L, LS, l);
  while (LS->current != del) {
    checkbuffer(L, 10, l);
    switch (LS->current) {
      case EOZ:  case '\n':
        save(L, '\0', l);
        luaX_error(LS, "unfinished string", TK_STRING);
        break;
      case '\\':
        next(LS);
        switch (LS->current) {
          case 'a': save(L, '\a', l); next(LS); break;
          case 'b': save(L, '\b', l); next(LS); break;
          case 'f': save(L, '\f', l); next(LS); break;
          case 'n': save(L, '\n', l); next(LS); break;
          case 'r': save(L, '\r', l); next(LS); break;
          case 't': save(L, '\t', l); next(LS); break;
          case 'v': save(L, '\v', l); next(LS); break;
          case '\n': save(L, '\n', l); inclinenumber(LS); break;
          case '0': case '1': case '2': case '3': case '4':
          case '5': case '6': case '7': case '8': case '9': {
            int c = 0;
            int i = 0;
            do {
              c = 10*c + (LS->current-'0');
              next(LS);
            } while (++i<3 && isdigit(LS->current));
            if (c != (unsigned char)c) {
              save(L, '\0', l);
              luaX_error(LS, "escape sequence too large", TK_STRING);
            }
            save(L, c, l);
            break;
          }
          default:
            save_and_next(L, LS, l);
        }
        break;
      default:
        save_and_next(L, LS, l);
    }
  }
  save_and_next(L, LS, l);
  save(L, '\0', l);
  seminfo->ts = luaS_newlstr(L, L->Mbuffer+1, l-3);
}
