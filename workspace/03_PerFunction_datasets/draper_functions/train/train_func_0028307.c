read_long_string (LexState *LS) {
  int cont = 0;
  for (;;) {
    switch (LS->current) {
      case EOZ:
        luaX_error(LS, "unfinished long string");
        return EOS;
      case '[':
        save_and_next(LS);
        if (LS->current == '[') {
          cont++;
          save_and_next(LS);
        }
        continue;
      case ']':
        save_and_next(LS);
        if (LS->current == ']') {
          if (cont == 0) goto endloop;
          cont--;
          save_and_next(LS);
        }
        continue;
      case '\n':
        save('\n');
        inclinenumber(LS);
        continue;
      default:
        save_and_next(LS);
    }
  } endloop:
  save_and_next(LS);
  LS->seminfo.ts = luaS_newlstr(L->Mbuffer+(L->Mbuffbase+2),
                          L->Mbuffnext-L->Mbuffbase-4);
  return STRING;
}
