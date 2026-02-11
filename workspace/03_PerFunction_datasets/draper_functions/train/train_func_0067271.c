use_pointer_for_field (tree decl, omp_context *shared_ctx)
{
  if (AGGREGATE_TYPE_P (TREE_TYPE (decl)))
    return true;


  if (shared_ctx)
    {


      if (TREE_STATIC (decl) || DECL_EXTERNAL (decl))
	return true;


      if (TREE_CODE (decl) != RESULT_DECL && DECL_HAS_VALUE_EXPR_P (decl))
	return true;


      if (TREE_ADDRESSABLE (decl))
	return true;


      if (!TREE_READONLY (decl) && shared_ctx->is_nested)
	{
	  omp_context *up;

	  for (up = shared_ctx->outer; up; up = up->outer)
	    if (is_taskreg_ctx (up) && maybe_lookup_decl (decl, up))
	      break;

	  if (up)
	    {
	      tree c;

	      for (c = gimple_omp_taskreg_clauses (up->stmt);
		   c; c = OMP_CLAUSE_CHAIN (c))
		if (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		    && OMP_CLAUSE_DECL (c) == decl)
		  break;

	      if (c)
		goto maybe_mark_addressable_and_ret;
	    }
	}


      if (!TREE_READONLY (decl) && is_task_ctx (shared_ctx))
	{
	  tree outer;
	maybe_mark_addressable_and_ret:
	  outer = maybe_lookup_decl_in_outer_ctx (decl, shared_ctx);
	  if (is_gimple_reg (outer))
	    {


	      if (!task_shared_vars)
		task_shared_vars = BITMAP_ALLOC (NULL);
	      bitmap_set_bit (task_shared_vars, DECL_UID (outer));
	      TREE_ADDRESSABLE (outer) = 1;
	    }
	  return true;
	}
    }

  return false;
}
