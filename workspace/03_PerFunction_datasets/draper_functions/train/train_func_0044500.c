execute_warn_function_return (void)
{
  source_location location;
  gimple last;
  edge e;
  edge_iterator ei;


  if (TREE_THIS_VOLATILE (cfun->decl)
      && EDGE_COUNT (EXIT_BLOCK_PTR->preds) > 0)
    {
      location = UNKNOWN_LOCATION;
      FOR_EACH_EDGE (e, ei, EXIT_BLOCK_PTR->preds)
	{
	  last = last_stmt (e->src);
	  if ((gimple_code (last) == GIMPLE_RETURN
	       || gimple_call_builtin_p (last, BUILT_IN_RETURN))
	      && (location = gimple_location (last)) != UNKNOWN_LOCATION)
	    break;
	}
      if (location == UNKNOWN_LOCATION)
	location = cfun->function_end_locus;
      warning_at (location, 0, "%<noreturn%> function does return");
    }


  else if (warn_return_type
	   && !TREE_NO_WARNING (cfun->decl)
	   && EDGE_COUNT (EXIT_BLOCK_PTR->preds) > 0
	   && !VOID_TYPE_P (TREE_TYPE (TREE_TYPE (cfun->decl))))
    {
      FOR_EACH_EDGE (e, ei, EXIT_BLOCK_PTR->preds)
	{
	  gimple last = last_stmt (e->src);
	  if (gimple_code (last) == GIMPLE_RETURN
	      && gimple_return_retval (last) == NULL
	      && !gimple_no_warning_p (last))
	    {
	      location = gimple_location (last);
	      if (location == UNKNOWN_LOCATION)
		  location = cfun->function_end_locus;
	      warning_at (location, OPT_Wreturn_type, "control reaches end of non-void function");
	      TREE_NO_WARNING (cfun->decl) = 1;
	      break;
	    }
	}
    }
  return 0;
}
