assemble_thunks_and_aliases (struct cgraph_node *node)
{
  struct cgraph_edge *e;
  int i;
  struct ipa_ref *ref;

  for (e = node->callers; e;)
    if (e->caller->thunk.thunk_p)
      {
	struct cgraph_node *thunk = e->caller;

	e = e->next_caller;
	assemble_thunks_and_aliases (thunk);
        assemble_thunk (thunk);
      }
    else
      e = e->next_caller;
  for (i = 0; ipa_ref_list_referring_iterate (&node->symbol.ref_list,
					     i, ref); i++)
    if (ref->use == IPA_REF_ALIAS)
      {
	struct cgraph_node *alias = ipa_ref_referring_node (ref);
        bool saved_written = TREE_ASM_WRITTEN (alias->thunk.alias);


	TREE_ASM_WRITTEN (alias->thunk.alias) = 1;
	do_assemble_alias (alias->symbol.decl,
			   DECL_ASSEMBLER_NAME (alias->thunk.alias));
	assemble_thunks_and_aliases (alias);
	TREE_ASM_WRITTEN (alias->thunk.alias) = saved_written;
      }
}
