gt_style_get_num_with_track(const GtStyle *sty,
                                               const char *section,
                                               const char *key, double *val,
                                               GtFeatureNode *gn,
                                               const GtStr *track_id,
                                               GtError *err)
{
#ifndef NDEBUG
  int stack_size;
#endif
  int i = 0;
  gt_assert(sty && key && section && val);
  gt_error_check(err);
  gt_rwlock_wrlock(sty->lock);
#ifndef NDEBUG
  stack_size = lua_gettop(sty->L);
#endif

  i = style_find_section_for_getting(sty, section);

  if (i < 0) {
    gt_assert(lua_gettop(sty->L) == stack_size);
    gt_rwlock_unlock(sty->lock);
    return GT_STYLE_QUERY_NOT_SET;
  }

  lua_getfield(sty->L, -1, key);


  if (lua_isfunction(sty->L, -1))
  {
    int num_of_args = 0;
    if (gn) {
      GtGenomeNode *gn_lua = gt_genome_node_ref((GtGenomeNode*) gn);
      gt_lua_genome_node_push(sty->L, gn_lua);
      num_of_args++;
      if (track_id) {
        lua_pushstring(sty->L, gt_str_get(track_id));
        num_of_args++;
      }
    }
    if (lua_pcall(sty->L, num_of_args, 1, 0) != 0) {
      gt_error_set(err, "%s", lua_tostring(sty->L, -1));
      lua_pop(sty->L, 3);
      gt_assert(lua_gettop(sty->L) == stack_size);
      gt_rwlock_unlock(sty->lock);
      return GT_STYLE_QUERY_ERROR;
    }
  }

  if (lua_isnil(sty->L, -1) || !lua_isnumber(sty->L, -1)) {
    lua_pop(sty->L, i+1);
    gt_assert(lua_gettop(sty->L) == stack_size);
    gt_rwlock_unlock(sty->lock);
    return GT_STYLE_QUERY_NOT_SET;
  } else i++;

  *val = lua_tonumber(sty->L, -1);

  lua_pop(sty->L, i);
  gt_assert(lua_gettop(sty->L) == stack_size);
  gt_rwlock_unlock(sty->lock);
  return GT_STYLE_QUERY_OK;
}
