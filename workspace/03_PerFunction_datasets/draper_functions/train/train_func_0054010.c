str_lower (void) {
  long l;
  int i;
  char *s = luaL_check_lstr(1, &l);
  luaL_resetbuffer();
  for (i=0; i<l; i++)
    luaL_addchar(tolower((unsigned char)(s[i])));
  closeandpush();
}
