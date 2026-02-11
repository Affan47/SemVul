base_derived_from (tree derived, tree base)
{
  tree probe;

  for (probe = base; probe; probe = BINFO_INHERITANCE_CHAIN (probe))
    {
      if (probe == derived)
	return true;
      else if (TREE_VIA_VIRTUAL (probe))


	return purpose_member (BINFO_TYPE (probe),
			       CLASSTYPE_VBASECLASSES (BINFO_TYPE (derived)))
	  != NULL_TREE;
    }
  return false;
}
