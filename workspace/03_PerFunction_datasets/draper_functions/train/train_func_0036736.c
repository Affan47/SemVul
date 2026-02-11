gt_script_filter_run(GtScriptFilter *sf, GtFeatureNode *gf,
                         bool *select_node, GtError *err)
{
  int had_err = 0;
#ifndef NDEBUG
  int stack_size;
#endif
  GtGenomeNode *gn_lua;

#ifndef NDEBUG
  stack_size = lua_gettop(sf->L);
#endif

  if (!had_err) {
    lua_getglobal(sf->L, "filter");
    if (lua_isnil(sf->L, -1)) {
      gt_error_set(err, "function 'filter' is not defined");
      had_err = -1;
      lua_pop(sf->L, 1);
    }
  }

  if (!had_err) {
    gn_lua = gt_genome_node_ref((GtGenomeNode*) gf);
    gt_lua_genome_node_push(sf->L, gn_lua);

    if (lua_pcall(sf->L, 1, 1, 0) != 0) {
      gt_error_set(err, "error running function 'filter': %s",
                   lua_tostring(sf->L, -1));
      lua_pop(sf->L, 1);
      had_err = -1;
    }
  }

  if (!had_err && !lua_isboolean(sf->L, -1)) {
    gt_error_set(err, "function 'filter' must return boolean");
    lua_pop(sf->L, 1);
    had_err = -1;
  }

  if (!had_err) {
    *select_node = lua_toboolean(sf->L, -1);
    lua_pop(sf->L, 1);
  }
  gt_assert(lua_gettop(sf->L) == stack_size);

  return had_err;
}
