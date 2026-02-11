pmain (lua_State *l) {
  struct Smain *s = (struct Smain *)lua_touserdata(l, 1);
  int status;
  int interactive = 0;
  if (s->argv[0] && s->argv[0][0]) progname = s->argv[0];
  L = l;
  lua_userinit(l);
  status = handle_luainit();
  if (status == 0) {
    status = handle_argv(s->argv, &interactive);
    if (status == 0 && interactive) manual_input();
  }
  s->status = status;
  return 0;
}
