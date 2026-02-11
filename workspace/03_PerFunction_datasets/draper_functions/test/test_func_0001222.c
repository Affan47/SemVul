io_date (void) {
  char b[256];
  char *s = luaL_opt_string(1, "%c");
  struct tm *tm;
  time_t t;
  time(&t); tm = localtime(&t);
  if (strftime(b,sizeof(b),s,tm))
    lua_pushstring(b);
  else
    lua_error("invalid `date' format");
}
