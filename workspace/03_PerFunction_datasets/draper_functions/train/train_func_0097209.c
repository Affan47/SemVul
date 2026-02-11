dfs_debug_mark (tree binfo, void * )
{
  tree t = BINFO_TYPE (binfo);

  if (CLASSTYPE_DEBUG_REQUESTED (t))
    return dfs_skip_bases;

  CLASSTYPE_DEBUG_REQUESTED (t) = 1;

  return NULL_TREE;
}
