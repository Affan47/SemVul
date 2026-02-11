str_upper (void)
{
  char *s;
  luaI_emptybuff();
  for (s = luaL_check_string(1); *s; s++)
    luaI_addchar(toupper((unsigned char)*s));
  lua_pushstring(luaI_addchar(0));
}
