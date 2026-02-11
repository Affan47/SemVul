io_read (void)
{
  char *buff;
  char *p = lua_opt_string(1, "[^\n]*{\n}", "read");
  int inskip = 0;
  int c = NEED_OTHER;
  luaI_addchar(0);
  while (*p) {
    if (*p == '{' || *p == '}') {
      inskip = (*p == '{');
      p++;
    }
    else {
      char *ep = item_end(p);
      int m;
      if (c == NEED_OTHER) c = getc(lua_infile);
      m = (c == EOF) ? 0 : singlematch((char)c, p);
      if (m) {
        if (!inskip) luaI_addchar(c);
        c = NEED_OTHER;
      }
      switch (*ep) {
        case '*':
          if (!m) p = ep+1;
          break;
        case '?':
          p = ep+1;
          break;
        default:
          if (m) p = ep;
          else
            goto break_while;
      }
    }
  } break_while:
  if (c >= 0)
     ungetc(c, lua_infile);
  buff = luaI_addchar(0);
  if (*buff != 0 || *p == 0)
    lua_pushstring(buff);
}
