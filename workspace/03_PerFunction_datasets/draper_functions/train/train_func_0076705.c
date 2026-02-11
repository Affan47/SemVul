end_of_class (tree t, int include_virtuals_p)
{
  tree result = size_zero_node;
  vec<tree, va_gc> *vbases;
  tree binfo;
  tree base_binfo;
  tree offset;
  int i;

  for (binfo = TYPE_BINFO (t), i = 0;
       BINFO_BASE_ITERATE (binfo, i, base_binfo); ++i)
    {
      if (!include_virtuals_p
	  && BINFO_VIRTUAL_P (base_binfo)
	  && (!BINFO_PRIMARY_P (base_binfo)
	      || BINFO_INHERITANCE_CHAIN (base_binfo) != TYPE_BINFO (t)))
	continue;

      offset = end_of_base (base_binfo);
      if (INT_CST_LT_UNSIGNED (result, offset))
	result = offset;
    }


  if (abi_version_at_least (2) && include_virtuals_p)
    for (vbases = CLASSTYPE_VBASECLASSES (t), i = 0;
	 vec_safe_iterate (vbases, i, &base_binfo); i++)
      {
	offset = end_of_base (base_binfo);
	if (INT_CST_LT_UNSIGNED (result, offset))
	  result = offset;
      }

  return result;
}
