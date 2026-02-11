ipa_tm_transform_clone (struct cgraph_node *node)
{
  struct tm_ipa_cg_data *d;
  bool need_ssa_rename;

  d = get_cg_data (&node, true);


  if (!node->callees && !node->indirect_calls && !d->irrevocable_blocks_clone)
    return;

  push_cfun (DECL_STRUCT_FUNCTION (d->clone->symbol.decl));
  calculate_dominance_info (CDI_DOMINATORS);

  need_ssa_rename =
    ipa_tm_transform_calls (d->clone, NULL, single_succ (ENTRY_BLOCK_PTR),
			    d->irrevocable_blocks_clone);

  if (need_ssa_rename)
    update_ssa (TODO_update_ssa_only_virtuals);

  pop_cfun ();
}
