lto_input_ts_binfo_tree_pointers (struct lto_input_block *ib,
				  struct data_in *data_in, tree expr)
{
  unsigned i, len;
  tree t;


  do
    {
      t = lto_input_tree (ib, data_in);
      if (t)
	VEC_quick_push (tree, BINFO_BASE_BINFOS (expr), t);
    }
  while (t);

  BINFO_OFFSET (expr) = lto_input_tree (ib, data_in);
  BINFO_VTABLE (expr) = lto_input_tree (ib, data_in);
  BINFO_VIRTUALS (expr) = lto_input_tree (ib, data_in);
  BINFO_VPTR_FIELD (expr) = lto_input_tree (ib, data_in);

  len = lto_input_uleb128 (ib);
  if (len > 0)
    {
      VEC_reserve_exact (tree, gc, BINFO_BASE_ACCESSES (expr), len);
      for (i = 0; i < len; i++)
	{
	  tree a = lto_input_tree (ib, data_in);
	  VEC_quick_push (tree, BINFO_BASE_ACCESSES (expr), a);
	}
    }

  BINFO_INHERITANCE_CHAIN (expr) = lto_input_tree (ib, data_in);
  BINFO_SUBVTT_INDEX (expr) = lto_input_tree (ib, data_in);
  BINFO_VPTR_INDEX (expr) = lto_input_tree (ib, data_in);
}
