get_static_chain (struct nesting_info *info, tree target_context,
		  gimple_stmt_iterator *gsi)
{
  struct nesting_info *i;
  tree x;

  if (info->context == target_context)
    {
      x = build_addr (info->frame_decl, target_context);
    }
  else
    {
      x = get_chain_decl (info);

      for (i = info->outer; i->context != target_context; i = i->outer)
	{
	  tree field = get_chain_field (i);

	  x = build_simple_mem_ref (x);
	  x = build3 (COMPONENT_REF, TREE_TYPE (field), x, field, NULL_TREE);
	  x = init_tmp_var (info, x, gsi);
	}
    }

  return x;
}
