decide_is_function_needed (struct cgraph_node *node, tree decl)
{


  if (node->needed)
    return true;


  if (TREE_PUBLIC (decl) && !DECL_COMDAT (decl) && !DECL_EXTERNAL (decl))
    return true;


  if (DECL_STATIC_CONSTRUCTOR (decl) || DECL_STATIC_DESTRUCTOR (decl))
    return true;


  if (lookup_attribute ("used", DECL_ATTRIBUTES (decl)))
    return true;


  if (DECL_ASSEMBLER_NAME_SET_P (decl)
      && TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl)))
    return true;

  if (flag_unit_at_a_time)
    return false;


  if (DECL_EXTERNAL (decl))
    return false;

  if (DECL_COMDAT (decl))
    return false;
  if (!DECL_INLINE (decl)
      || (!node->local.disregard_inline_limits


	  && !DECL_DECLARED_INLINE_P (decl)
	  && (!node->local.inlinable || !cgraph_default_inline_p (node))))
    return true;

  return false;
}
