finish_anon_union (tree anon_union_decl)
{
  tree type;
  tree main_decl;
  bool public_p;

  if (anon_union_decl == error_mark_node)
    return;

  type = TREE_TYPE (anon_union_decl);
  public_p = TREE_PUBLIC (anon_union_decl);


  DECL_CONTEXT (anon_union_decl) = DECL_CONTEXT (TYPE_NAME (type));

  if (TYPE_FIELDS (type) == NULL_TREE)
    return;

  if (public_p)
    {
      error ("namespace-scope anonymous aggregates must be static");
      return;
    }

  main_decl = build_anon_union_vars (type, anon_union_decl);
  if (main_decl == error_mark_node)
    return;
  if (main_decl == NULL_TREE)
    {
      warning (0, "anonymous union with no members");
      return;
    }

  if (!processing_template_decl)
    {

      DECL_NAME (anon_union_decl) = DECL_NAME (main_decl);
      maybe_commonize_var (anon_union_decl);
      if (TREE_STATIC (anon_union_decl) || DECL_EXTERNAL (anon_union_decl))
	mangle_decl (anon_union_decl);
      DECL_NAME (anon_union_decl) = NULL_TREE;
    }

  pushdecl (anon_union_decl);
  if (building_stmt_list_p ()
      && at_function_scope_p ())
    add_decl_expr (anon_union_decl);
  else if (!processing_template_decl)
    rest_of_decl_compilation (anon_union_decl,
			      toplevel_bindings_p (), at_eof);
}
