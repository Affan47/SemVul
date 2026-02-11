gimplify_bind_expr (tree *expr_p, gimple_seq *pre_p)
{
  tree bind_expr = *expr_p;
  bool old_save_stack = gimplify_ctxp->save_stack;
  tree t;
  gimple gimple_bind;
  gimple_seq body, cleanup;
  gimple stack_save;

  tree temp = voidify_wrapper_expr (bind_expr, NULL);


  for (t = BIND_EXPR_VARS (bind_expr); t ; t = DECL_CHAIN (t))
    {
      if (TREE_CODE (t) == VAR_DECL)
	{
	  struct gimplify_omp_ctx *ctx = gimplify_omp_ctxp;


	  if (ctx && !DECL_EXTERNAL (t)
	      && (! DECL_SEEN_IN_BIND_EXPR_P (t)
		  || splay_tree_lookup (ctx->variables,
					(splay_tree_key) t) == NULL))
	    omp_add_variable (gimplify_omp_ctxp, t, GOVD_LOCAL | GOVD_SEEN);

	  DECL_SEEN_IN_BIND_EXPR_P (t) = 1;

	  if (DECL_HARD_REGISTER (t) && !is_global_var (t) && cfun)
	    cfun->has_local_explicit_reg_vars = true;
	}


      if ((TREE_CODE (TREE_TYPE (t)) == COMPLEX_TYPE
	   || TREE_CODE (TREE_TYPE (t)) == VECTOR_TYPE)
	  && !TREE_THIS_VOLATILE (t)
	  && (TREE_CODE (t) == VAR_DECL && !DECL_HARD_REGISTER (t))
	  && !needs_to_live_in_memory (t))
	DECL_GIMPLE_REG_P (t) = 1;
    }

  gimple_bind = gimple_build_bind (BIND_EXPR_VARS (bind_expr), NULL,
                                   BIND_EXPR_BLOCK (bind_expr));
  gimple_push_bind_expr (gimple_bind);

  gimplify_ctxp->save_stack = false;


  body = NULL;
  gimplify_stmt (&BIND_EXPR_BODY (bind_expr), &body);
  gimple_bind_set_body (gimple_bind, body);

  cleanup = NULL;
  stack_save = NULL;
  if (gimplify_ctxp->save_stack)
    {
      gimple stack_restore;


      build_stack_save_restore (&stack_save, &stack_restore);

      gimplify_seq_add_stmt (&cleanup, stack_restore);
    }


  for (t = BIND_EXPR_VARS (bind_expr); t ; t = DECL_CHAIN (t))
    {
      if (TREE_CODE (t) == VAR_DECL
	  && !is_global_var (t)
	  && DECL_CONTEXT (t) == current_function_decl
	  && !DECL_HARD_REGISTER (t)
	  && !TREE_THIS_VOLATILE (t)
	  && !DECL_HAS_VALUE_EXPR_P (t)


	  && !is_gimple_reg (t))
	{
	  tree clobber = build_constructor (TREE_TYPE (t), NULL);
	  TREE_THIS_VOLATILE (clobber) = 1;
	  gimplify_seq_add_stmt (&cleanup, gimple_build_assign (t, clobber));
	}
    }

  if (cleanup)
    {
      gimple gs;
      gimple_seq new_body;

      new_body = NULL;
      gs = gimple_build_try (gimple_bind_body (gimple_bind), cleanup,
	  		     GIMPLE_TRY_FINALLY);

      if (stack_save)
	gimplify_seq_add_stmt (&new_body, stack_save);
      gimplify_seq_add_stmt (&new_body, gs);
      gimple_bind_set_body (gimple_bind, new_body);
    }

  gimplify_ctxp->save_stack = old_save_stack;
  gimple_pop_bind_expr ();

  gimplify_seq_add_stmt (pre_p, gimple_bind);

  if (temp)
    {
      *expr_p = temp;
      return GS_OK;
    }

  *expr_p = NULL_TREE;
  return GS_ALL_DONE;
}
