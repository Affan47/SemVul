gt_lua_export_metatable(lua_State *L, const char *metatable_desc)
{
  char *dot, *mt;
  gt_assert(L && metatable_desc);
  mt = gt_cstr_dup(metatable_desc);
  dot = strchr(mt, '.');
  gt_assert(dot);
  *dot = '_';
  lua_setglobal(L, mt);
  gt_free(mt);
}
