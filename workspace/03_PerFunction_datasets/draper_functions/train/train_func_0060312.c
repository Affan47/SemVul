dynamic_cast_base_recurse (tree subtype, tree binfo, bool is_via_virtual,
			   tree *offset_ptr)
{
  tree binfos, accesses;
  int i, n_baselinks;
  int worst = -2;

  if (BINFO_TYPE (binfo) == subtype)
    {
      if (is_via_virtual)
        return -1;
      else
        {
          *offset_ptr = BINFO_OFFSET (binfo);
          return 0;
        }
    }

  binfos = BINFO_BASETYPES (binfo);
  accesses = BINFO_BASEACCESSES (binfo);
  n_baselinks = binfos ? TREE_VEC_LENGTH (binfos) : 0;
  for (i = 0; i < n_baselinks; i++)
    {
      tree base_binfo = TREE_VEC_ELT (binfos, i);
      tree base_access = TREE_VEC_ELT (accesses, i);
      int rval;

      if (base_access != access_public_node)
        continue;
      rval = dynamic_cast_base_recurse
             (subtype, base_binfo,
              is_via_virtual || TREE_VIA_VIRTUAL (base_binfo), offset_ptr);
      if (worst == -2)
        worst = rval;
      else if (rval >= 0)
        worst = worst >= 0 ? -3 : worst;
      else if (rval == -1)
        worst = -1;
      else if (rval == -3 && worst != -1)
        worst = -3;
    }
  return worst;
}
