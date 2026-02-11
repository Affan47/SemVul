dfs_get_pure_virtuals (tree binfo, void *data)
{
  tree type = (tree) data;


  if (!BINFO_PRIMARY_P (binfo))
    {
      tree virtuals;

      for (virtuals = BINFO_VIRTUALS (binfo);
	   virtuals;
	   virtuals = TREE_CHAIN (virtuals))
	if (DECL_PURE_VIRTUAL_P (BV_FN (virtuals)))
	  vec_safe_push (CLASSTYPE_PURE_VIRTUALS (type), BV_FN (virtuals));
    }

  return NULL_TREE;
}
