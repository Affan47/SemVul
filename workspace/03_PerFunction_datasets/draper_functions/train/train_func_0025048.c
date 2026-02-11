contained_in_symbol (symtab_node node)
{

  if (lookup_attribute ("weakref",
			DECL_ATTRIBUTES (node->symbol.decl)))
    return node;
  if (cgraph_node *cnode = dyn_cast <cgraph_node> (node))
    {
      cnode = cgraph_function_node (cnode, NULL);
      if (cnode->global.inlined_to)
	cnode = cnode->global.inlined_to;
      return (symtab_node) cnode;
    }
  else if (varpool_node *vnode = dyn_cast <varpool_node> (node))
    return (symtab_node) varpool_variable_node (vnode, NULL);
  return node;
}
