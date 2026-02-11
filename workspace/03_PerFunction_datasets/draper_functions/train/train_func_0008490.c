perform_member_init (tree member, tree init)
{
  tree decl;
  tree type = TREE_TYPE (member);
  bool explicit;

  explicit = (init != NULL_TREE);


  if (warn_ecpp && !explicit && TREE_CODE (type) != ARRAY_TYPE)
    warning ("`%D' should be initialized in the member initialization "
	     "list",
	     member);

  if (init == void_type_node)
    init = NULL_TREE;


  decl = build_class_member_access_expr (current_class_ref, member,
					 NULL_TREE,
					 true);
  if (decl == error_mark_node)
    return;


  if (ANON_AGGR_TYPE_P (type))
    {
      if (init)
	{
	  init = build (INIT_EXPR, type, decl, TREE_VALUE (init));
	  finish_expr_stmt (init);
	}
    }
  else if (TYPE_NEEDS_CONSTRUCTING (type)
	   || (init && TYPE_HAS_CONSTRUCTOR (type)))
    {
      if (explicit
	  && TREE_CODE (type) == ARRAY_TYPE
	  && init != NULL_TREE
	  && TREE_CHAIN (init) == NULL_TREE
	  && TREE_CODE (TREE_TYPE (TREE_VALUE (init))) == ARRAY_TYPE)
	{

	  finish_expr_stmt (build_vec_init (decl, NULL_TREE, TREE_VALUE (init),
					    1));
	}
      else
	finish_expr_stmt (build_aggr_init (decl, init, 0));
    }
  else
    {
      if (init == NULL_TREE)
	{
	  if (explicit)
	    {
	      init = build_default_init (type, NULL_TREE);
	      if (TREE_CODE (type) == REFERENCE_TYPE)
		warning
		  ("default-initialization of `%#D', which has reference type",
		   member);
	    }

	  else if (TREE_CODE (type) == REFERENCE_TYPE)
	    pedwarn ("uninitialized reference member `%D'", member);
	  else if (CP_TYPE_CONST_P (type))
	    pedwarn ("uninitialized member `%D' with `const' type `%T'",
		     member, type);
	}
      else if (TREE_CODE (init) == TREE_LIST)


	init = build_x_compound_expr_from_list (init, "member initializer");

      if (init)
	finish_expr_stmt (build_modify_expr (decl, INIT_EXPR, init));
    }

  if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (type))
    {
      tree expr;

      expr = build_class_member_access_expr (current_class_ref, member,
					     NULL_TREE,
					     false);
      expr = build_delete (type, expr, sfk_complete_destructor,
			   LOOKUP_NONVIRTUAL|LOOKUP_DESTRUCTOR, 0);

      if (expr != error_mark_node)
	finish_eh_cleanup (expr);
    }
}
