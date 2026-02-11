look_for_tm_attr_overrides (tree type, tree fndecl)
{
  tree binfo = TYPE_BINFO (type);
  tree base_binfo;
  int ix, found = 0;

  for (ix = 0; BINFO_BASE_ITERATE (binfo, ix, base_binfo); ++ix)
    {
      tree o, basetype = BINFO_TYPE (base_binfo);

      if (!TYPE_POLYMORPHIC_P (basetype))
	continue;

      o = look_for_overrides_here (basetype, fndecl);
      if (o)
	found |= tm_attr_to_mask (find_tm_attribute
				  (TYPE_ATTRIBUTES (TREE_TYPE (o))));
      else
	found |= look_for_tm_attr_overrides (basetype, fndecl);
    }

  return found;
}
