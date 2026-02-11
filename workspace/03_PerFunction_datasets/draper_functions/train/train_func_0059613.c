scripting_GetStringResult(char **s) {
  int status;
  if(lua_isstring(L, -1)) {
    int size;
    status = 0;
    size = lua_strlen(L, -1) + 1;
    *s = malloc( size );
    memcpy( *s, lua_tostring(L, -1), size );

  } else
    status = 1;

  lua_pop(L, 1);
  return status;
}
