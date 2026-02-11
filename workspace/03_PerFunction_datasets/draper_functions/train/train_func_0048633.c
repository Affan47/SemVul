maybe_apply_pending_pragma_weaks (void)
{
  tree alias_id, id, decl;
  int i;
  pending_weak *pe;
  symtab_node target;

  if (vec_safe_is_empty (pending_weaks))
    return;

  FOR_EACH_VEC_ELT (*pending_weaks, i, pe)
    {
      alias_id = pe->name;
      id = pe->value;

      if (id == NULL)
	continue;

      target = symtab_node_for_asm (id);
      decl = build_decl (UNKNOWN_LOCATION,
			 target ? TREE_CODE (target->symbol.decl) : FUNCTION_DECL,
			 alias_id, default_function_type);

      DECL_ARTIFICIAL (decl) = 1;
      TREE_PUBLIC (decl) = 1;
      DECL_WEAK (decl) = 1;
      if (TREE_CODE (decl) == VAR_DECL)
	TREE_STATIC (decl) = 1;
      if (!target)
	{
	  error ("%q+D aliased to undefined symbol %qE",
		 decl, id);
	  continue;
	}

      assemble_alias (decl, id);
    }
}
