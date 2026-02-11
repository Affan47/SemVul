get_primary_binfo (tree binfo)
{
  tree primary_base;
  tree result;

  primary_base = CLASSTYPE_PRIMARY_BINFO (BINFO_TYPE (binfo));
  if (!primary_base)
    return NULL_TREE;

  result = copied_binfo (primary_base, binfo);
  return result;
}
