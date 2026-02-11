dfs_find_final_overrider_q (tree derived, int ix, void *data)
{
  tree binfo = BINFO_BASETYPE (derived, ix);
  find_final_overrider_data *ffod = (find_final_overrider_data *) data;

  if (TREE_VIA_VIRTUAL (binfo))
    *ffod->vpath++ = derived;

  return binfo;
}
