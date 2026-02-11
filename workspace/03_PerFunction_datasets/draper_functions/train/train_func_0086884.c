genome_node_lua_add_child(lua_State *L)
{
  GtGenomeNode **parent, **child;
  GtFeatureNode *pf, *cf;
  parent = check_genome_node(L, 1);
  child  = check_genome_node(L, 2);
  pf = gt_feature_node_try_cast(*parent);
  luaL_argcheck(L, pf, 1, "not a feature node");
  cf = gt_feature_node_try_cast(*child);
  luaL_argcheck(L, cf, 2, "not a feature node");
  gt_feature_node_add_child(pf, (GtFeatureNode*)
                                gt_genome_node_ref((GtGenomeNode*) cf));
  return 0;
}
