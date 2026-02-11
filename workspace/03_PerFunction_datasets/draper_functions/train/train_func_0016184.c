lto_symtab_merge_cgraph_nodes (void)
{
  struct cgraph_node *node, *alias, *next;
  lto_symtab_maybe_init_hash_table ();
  htab_traverse (lto_symtab_identifiers, lto_symtab_merge_cgraph_nodes_1, NULL);

  for (node = cgraph_nodes; node; node = node->next)
    for (alias = node->same_body; alias; alias = next)
      {
	next = alias->next;
	alias->thunk.alias = lto_symtab_prevailing_decl (alias->thunk.alias);
      }
}
