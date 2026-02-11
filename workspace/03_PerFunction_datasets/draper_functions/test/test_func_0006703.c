lower_omp_critical (gimple_stmt_iterator *gsi_p, omp_context *ctx)
{
  tree block;
  tree name, lock, unlock;
  gimple stmt = gsi_stmt (*gsi_p), bind;
  location_t loc = gimple_location (stmt);
  gimple_seq tbody;
  struct gimplify_ctx gctx;

  name = gimple_omp_critical_name (stmt);
  if (name)
    {
      tree decl;
      splay_tree_node n;

      if (!critical_name_mutexes)
	critical_name_mutexes
	  = splay_tree_new_ggc (splay_tree_compare_pointers,
				ggc_alloc_splay_tree_tree_node_tree_node_splay_tree_s,
				ggc_alloc_splay_tree_tree_node_tree_node_splay_tree_node_s);

      n = splay_tree_lookup (critical_name_mutexes, (splay_tree_key) name);
      if (n == NULL)
	{
	  char *new_str;

	  decl = create_tmp_var_raw (ptr_type_node, NULL);

	  new_str = ACONCAT ((".gomp_critical_user_",
			      IDENTIFIER_POINTER (name), NULL));
	  DECL_NAME (decl) = get_identifier (new_str);
	  TREE_PUBLIC (decl) = 1;
	  TREE_STATIC (decl) = 1;
	  DECL_COMMON (decl) = 1;
	  DECL_ARTIFICIAL (decl) = 1;
	  DECL_IGNORED_P (decl) = 1;
	  varpool_finalize_decl (decl);

	  splay_tree_insert (critical_name_mutexes, (splay_tree_key) name,
			     (splay_tree_value) decl);
	}
      else
	decl = (tree) n->value;

      lock = builtin_decl_explicit (BUILT_IN_GOMP_CRITICAL_NAME_START);
      lock = build_call_expr_loc (loc, lock, 1, build_fold_addr_expr_loc (loc, decl));

      unlock = builtin_decl_explicit (BUILT_IN_GOMP_CRITICAL_NAME_END);
      unlock = build_call_expr_loc (loc, unlock, 1,
				build_fold_addr_expr_loc (loc, decl));
    }
  else
    {
      lock = builtin_decl_explicit (BUILT_IN_GOMP_CRITICAL_START);
      lock = build_call_expr_loc (loc, lock, 0);

      unlock = builtin_decl_explicit (BUILT_IN_GOMP_CRITICAL_END);
      unlock = build_call_expr_loc (loc, unlock, 0);
    }

  push_gimplify_context (&gctx);

  block = make_node (BLOCK);
  bind = gimple_build_bind (NULL, NULL, block);
  gsi_replace (gsi_p, bind, true);
  gimple_bind_add_stmt (bind, stmt);

  tbody = gimple_bind_body (bind);
  gimplify_and_add (lock, &tbody);
  gimple_bind_set_body (bind, tbody);

  lower_omp (gimple_omp_body_ptr (stmt), ctx);
  gimple_omp_set_body (stmt, maybe_catch_exception (gimple_omp_body (stmt)));
  gimple_bind_add_seq (bind, gimple_omp_body (stmt));
  gimple_omp_set_body (stmt, NULL);

  tbody = gimple_bind_body (bind);
  gimplify_and_add (unlock, &tbody);
  gimple_bind_set_body (bind, tbody);

  gimple_bind_add_stmt (bind, gimple_build_omp_return (true));

  pop_gimplify_context (bind);
  gimple_bind_append_vars (bind, ctx->block_vars);
  BLOCK_VARS (block) = gimple_bind_vars (bind);
}
