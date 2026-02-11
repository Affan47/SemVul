finalize_must_preallocate (int must_preallocate, int num_actuals,
			   struct arg_data *args, struct args_size *args_size)
{


  if (! must_preallocate)
    {
      int partial_seen = 0;
      int copy_to_evaluate_size = 0;
      int i;

      for (i = 0; i < num_actuals && ! must_preallocate; i++)
	{
	  if (args[i].partial > 0 && ! args[i].pass_on_stack)
	    partial_seen = 1;
	  else if (partial_seen && args[i].reg == 0)
	    must_preallocate = 1;

	  if (TYPE_MODE (TREE_TYPE (args[i].tree_value)) == BLKmode
	      && (TREE_CODE (args[i].tree_value) == CALL_EXPR
		  || TREE_CODE (args[i].tree_value) == TARGET_EXPR
		  || TREE_CODE (args[i].tree_value) == COND_EXPR
		  || TREE_ADDRESSABLE (TREE_TYPE (args[i].tree_value))))
	    copy_to_evaluate_size
	      += int_size_in_bytes (TREE_TYPE (args[i].tree_value));
	}

      if (copy_to_evaluate_size * 2 >= args_size->constant
	  && args_size->constant > 0)
	must_preallocate = 1;
    }
  return must_preallocate;
}
