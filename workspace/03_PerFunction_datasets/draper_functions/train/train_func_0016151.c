convert_nonlocal_omp_clauses (tree *pclauses, struct walk_stmt_info *wi)
{
  struct nesting_info *const info = (struct nesting_info *) wi->info;
  bool need_chain = false, need_stmts = false;
  tree clause, decl;
  int dummy;
  bitmap new_suppress;

  new_suppress = BITMAP_GGC_ALLOC ();
  bitmap_copy (new_suppress, info->suppress_expansion);

  for (clause = *pclauses; clause ; clause = OMP_CLAUSE_CHAIN (clause))
    {
      switch (OMP_CLAUSE_CODE (clause))
	{
	case OMP_CLAUSE_REDUCTION:
	  if (OMP_CLAUSE_REDUCTION_PLACEHOLDER (clause))
	    need_stmts = true;
	  goto do_decl_clause;

	case OMP_CLAUSE_LASTPRIVATE:
	  if (OMP_CLAUSE_LASTPRIVATE_GIMPLE_SEQ (clause))
	    need_stmts = true;
	  goto do_decl_clause;

	case OMP_CLAUSE_PRIVATE:
	case OMP_CLAUSE_FIRSTPRIVATE:
	case OMP_CLAUSE_COPYPRIVATE:
	case OMP_CLAUSE_SHARED:
	do_decl_clause:
	  decl = OMP_CLAUSE_DECL (clause);
	  if (TREE_CODE (decl) == VAR_DECL
	      && (TREE_STATIC (decl) || DECL_EXTERNAL (decl)))
	    break;
	  if (decl_function_context (decl) != info->context)
	    {
	      bitmap_set_bit (new_suppress, DECL_UID (decl));
	      OMP_CLAUSE_DECL (clause) = get_nonlocal_debug_decl (info, decl);
	      if (OMP_CLAUSE_CODE (clause) != OMP_CLAUSE_PRIVATE)
		need_chain = true;
	    }
	  break;

	case OMP_CLAUSE_SCHEDULE:
	  if (OMP_CLAUSE_SCHEDULE_CHUNK_EXPR (clause) == NULL)
	    break;

	case OMP_CLAUSE_FINAL:
	case OMP_CLAUSE_IF:
	case OMP_CLAUSE_NUM_THREADS:
	  wi->val_only = true;
	  wi->is_lhs = false;
	  convert_nonlocal_reference_op (&OMP_CLAUSE_OPERAND (clause, 0),
	                                 &dummy, wi);
	  break;

	case OMP_CLAUSE_NOWAIT:
	case OMP_CLAUSE_ORDERED:
	case OMP_CLAUSE_DEFAULT:
	case OMP_CLAUSE_COPYIN:
	case OMP_CLAUSE_COLLAPSE:
	case OMP_CLAUSE_UNTIED:
	case OMP_CLAUSE_MERGEABLE:
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  info->suppress_expansion = new_suppress;

  if (need_stmts)
    for (clause = *pclauses; clause ; clause = OMP_CLAUSE_CHAIN (clause))
      switch (OMP_CLAUSE_CODE (clause))
	{
	case OMP_CLAUSE_REDUCTION:
	  if (OMP_CLAUSE_REDUCTION_PLACEHOLDER (clause))
	    {
	      tree old_context
		= DECL_CONTEXT (OMP_CLAUSE_REDUCTION_PLACEHOLDER (clause));
	      DECL_CONTEXT (OMP_CLAUSE_REDUCTION_PLACEHOLDER (clause))
		= info->context;
	      walk_body (convert_nonlocal_reference_stmt,
			 convert_nonlocal_reference_op, info,
			 &OMP_CLAUSE_REDUCTION_GIMPLE_INIT (clause));
	      walk_body (convert_nonlocal_reference_stmt,
			 convert_nonlocal_reference_op, info,
			 &OMP_CLAUSE_REDUCTION_GIMPLE_MERGE (clause));
	      DECL_CONTEXT (OMP_CLAUSE_REDUCTION_PLACEHOLDER (clause))
		= old_context;
	    }
	  break;

	case OMP_CLAUSE_LASTPRIVATE:
	  walk_body (convert_nonlocal_reference_stmt,
		     convert_nonlocal_reference_op, info,
		     &OMP_CLAUSE_LASTPRIVATE_GIMPLE_SEQ (clause));
	  break;

	default:
	  break;
	}

  return need_chain;
}
