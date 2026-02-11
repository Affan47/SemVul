optimize_omp_library_calls (gimple entry_stmt)
{
  basic_block bb;
  gimple_stmt_iterator gsi;
  tree thr_num_tree = builtin_decl_explicit (BUILT_IN_OMP_GET_THREAD_NUM);
  tree thr_num_id = DECL_ASSEMBLER_NAME (thr_num_tree);
  tree num_thr_tree = builtin_decl_explicit (BUILT_IN_OMP_GET_NUM_THREADS);
  tree num_thr_id = DECL_ASSEMBLER_NAME (num_thr_tree);
  bool untied_task = (gimple_code (entry_stmt) == GIMPLE_OMP_TASK
		      && find_omp_clause (gimple_omp_task_clauses (entry_stmt),
					  OMP_CLAUSE_UNTIED) != NULL);

  FOR_EACH_BB (bb)
    for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
      {
	gimple call = gsi_stmt (gsi);
	tree decl;

	if (is_gimple_call (call)
	    && (decl = gimple_call_fndecl (call))
	    && DECL_EXTERNAL (decl)
	    && TREE_PUBLIC (decl)
	    && DECL_INITIAL (decl) == NULL)
	  {
	    tree built_in;

	    if (DECL_NAME (decl) == thr_num_id)
	      {


		if (untied_task)
		  continue;
		built_in = builtin_decl_explicit (BUILT_IN_OMP_GET_THREAD_NUM);
	      }
	    else if (DECL_NAME (decl) == num_thr_id)
	      built_in = builtin_decl_explicit (BUILT_IN_OMP_GET_NUM_THREADS);
	    else
	      continue;

	    if (DECL_ASSEMBLER_NAME (decl) != DECL_ASSEMBLER_NAME (built_in)
		|| gimple_call_num_args (call) != 0)
	      continue;

	    if (flag_exceptions && !TREE_NOTHROW (decl))
	      continue;

	    if (TREE_CODE (TREE_TYPE (decl)) != FUNCTION_TYPE
		|| !types_compatible_p (TREE_TYPE (TREE_TYPE (decl)),
					TREE_TYPE (TREE_TYPE (built_in))))
	      continue;

	    gimple_call_set_fndecl (call, built_in);
	  }
      }
}
