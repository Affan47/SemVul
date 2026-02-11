str_sub (void)
{
  char *s = luaL_check_string(1);
  long l = strlen(s);
  long start = (long)luaL_check_number(2);
  long end = (long)luaL_opt_number(3, -1);
  if (start < 0) start = l+start+1;
  if (end < 0) end = l+end+1;
  if (1 <= start && start <= end && end <= l) {
    luaI_emptybuff();
    addnchar(s+start-1, end-start+1);
    lua_pushstring(luaI_addchar(0));
  }
  else lua_pushstring("");
}
