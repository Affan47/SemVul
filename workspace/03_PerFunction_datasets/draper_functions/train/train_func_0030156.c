dfs_initialize_vtbl_ptrs (tree binfo, void *data)
{
  if ((!BINFO_PRIMARY_P (binfo) || TREE_VIA_VIRTUAL (binfo))
      && CLASSTYPE_VFIELDS (BINFO_TYPE (binfo)))
    {
      tree base_ptr = TREE_VALUE ((tree) data);

      base_ptr = build_base_path (PLUS_EXPR, base_ptr, binfo, 1);

      expand_virtual_init (binfo, base_ptr);
    }

  BINFO_MARKED (binfo) = 1;

  return NULL_TREE;
}
