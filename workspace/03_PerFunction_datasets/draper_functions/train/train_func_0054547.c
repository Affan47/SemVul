str_ascii (void)
{
  char *s = luaL_check_string(1);
  long pos = (long)luaL_opt_number(2, 1) - 1;
  luaL_arg_check(0<=pos && pos<strlen(s), 2,  "out of range");
  lua_pushnumber((unsigned char)s[pos]);
}
