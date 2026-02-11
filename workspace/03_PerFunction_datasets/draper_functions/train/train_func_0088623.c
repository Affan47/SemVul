cxx_maybe_build_cleanup (tree decl, tsubst_flags_t complain)
{
  tree type;
  tree attr;
  tree cleanup;


  cleanup = NULL_TREE;

  if (error_operand_p (decl))
    return cleanup;


  attr = lookup_attribute ("cleanup", DECL_ATTRIBUTES (decl));
  if (attr)
    {
      tree id;
      tree fn;
      tree arg;


      id = TREE_VALUE (TREE_VALUE (attr));


      fn = lookup_name (id);
      arg = build_address (decl);
      mark_used (decl);
      cleanup = cp_build_function_call_nary (fn, complain, arg, NULL_TREE);
      if (cleanup == error_mark_node)
	return error_mark_node;
    }

  type = TREE_TYPE (decl);
  if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (type))
    {
      int flags = LOOKUP_NORMAL|LOOKUP_DESTRUCTOR;
      bool has_vbases = (TREE_CODE (type) == RECORD_TYPE
			 && CLASSTYPE_VBASECLASSES (type));
      tree addr;
      tree call;

      if (TREE_CODE (type) == ARRAY_TYPE)
	addr = decl;
      else
	addr = build_address (decl);


      if (!has_vbases || flag_expensive_optimizations)
	flags |= LOOKUP_NONVIRTUAL;

      call = build_delete (TREE_TYPE (addr), addr,
			   sfk_complete_destructor, flags, 0, complain);
      if (call == error_mark_node)
	cleanup = error_mark_node;
      else if (cleanup)
	cleanup = cp_build_compound_expr (cleanup, call, complain);
      else
	cleanup = call;
    }


  if (cleanup != NULL && EXPR_P (cleanup))
    SET_EXPR_LOCATION (cleanup, UNKNOWN_LOCATION);
  return cleanup;
}
