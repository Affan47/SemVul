dfs_walk_once_accessible (tree binfo, bool friends_p,
			    tree (*pre_fn) (tree, void *),
			    tree (*post_fn) (tree, void *), void *data)
{
  bool diamond_shaped = CLASSTYPE_DIAMOND_SHAPED_P (BINFO_TYPE (binfo));
  tree rval = dfs_walk_once_accessible_r (binfo, friends_p, diamond_shaped,
					  pre_fn, post_fn, data);

  if (diamond_shaped)
    {
      if (!BINFO_INHERITANCE_CHAIN (binfo))
	{


	  vec<tree, va_gc> *vbases;
	  unsigned ix;
	  tree base_binfo;

	  for (vbases = CLASSTYPE_VBASECLASSES (BINFO_TYPE (binfo)), ix = 0;
	       vec_safe_iterate (vbases, ix, &base_binfo); ix++)
	    BINFO_MARKED (base_binfo) = 0;
	}
      else
	dfs_unmark_r (binfo);
    }
  return rval;
}
