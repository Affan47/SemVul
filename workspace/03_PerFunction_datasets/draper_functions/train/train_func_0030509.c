gff3_visitor_lua_new(lua_State *L)
{
  GtNodeVisitor **gv;
  gt_assert(L);

  gv = lua_newuserdata(L, sizeof (GtNodeVisitor*));
  *gv = gt_gff3_visitor_new(NULL);
  gt_assert(*gv);
  luaL_getmetatable(L, GENOME_VISITOR_METATABLE);
  lua_setmetatable(L, -2);
  return 1;
}
