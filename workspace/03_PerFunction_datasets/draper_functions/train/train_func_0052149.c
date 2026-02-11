build_vtbl_ref_1 (tree instance, tree idx)
{
  tree aref;
  tree vtbl = NULL_TREE;


  int cdtorp = 0;
  tree fixed_type = fixed_type_or_null (instance, NULL, &cdtorp);

  tree basetype = non_reference (TREE_TYPE (instance));

  if (fixed_type && !cdtorp)
    {
      tree binfo = lookup_base (fixed_type, basetype,
				ba_unique | ba_quiet, NULL);
      if (binfo)
	vtbl = unshare_expr (BINFO_VTABLE (binfo));
    }

  if (!vtbl)
    vtbl = build_vfield_ref (instance, basetype);

  aref = build_array_ref (input_location, vtbl, idx);
  TREE_CONSTANT (aref) |= TREE_CONSTANT (vtbl) && TREE_CONSTANT (idx);

  return aref;
}
