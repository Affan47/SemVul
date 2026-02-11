mark_load (gimple stmt, tree t, tree, void *data)
{
  t = get_base_address (t);
  if (t && TREE_CODE (t) == FUNCTION_DECL)
    {


      struct cgraph_node *node = cgraph_get_create_real_symbol_node (t);
      cgraph_mark_address_taken_node (node);
      ipa_record_reference ((symtab_node)data,
			    (symtab_node)node,
			    IPA_REF_ADDR, stmt);
    }
  else if (t && TREE_CODE (t) == VAR_DECL
	   && (TREE_STATIC (t) || DECL_EXTERNAL (t)))
    {
      struct varpool_node *vnode = varpool_node_for_decl (t);

      ipa_record_reference ((symtab_node)data,
			    (symtab_node)vnode,
			    IPA_REF_LOAD, stmt);
    }
  return false;
}
