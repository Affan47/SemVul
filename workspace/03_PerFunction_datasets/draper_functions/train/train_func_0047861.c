tsubst_default_argument (tree fn, tree type, tree arg, tsubst_flags_t complain)
{
  tree saved_class_ptr = NULL_TREE;
  tree saved_class_ref = NULL_TREE;
  int errs = errorcount + sorrycount;


  if (TREE_CODE (arg) == DEFAULT_ARG)
    return arg;


  push_access_scope (fn);

  if (cfun)
    {
      saved_class_ptr = current_class_ptr;
      cp_function_chain->x_current_class_ptr = NULL_TREE;
      saved_class_ref = current_class_ref;
      cp_function_chain->x_current_class_ref = NULL_TREE;
    }

  push_deferring_access_checks(dk_no_deferred);


  ++function_depth;
  arg = tsubst_expr (arg, DECL_TI_ARGS (fn),
		     complain, NULL_TREE,
		     false);
  --function_depth;
  pop_deferring_access_checks();


  if (cfun)
    {
      cp_function_chain->x_current_class_ptr = saved_class_ptr;
      cp_function_chain->x_current_class_ref = saved_class_ref;
    }

  if (errorcount+sorrycount > errs
      && (complain & tf_warning_or_error))
    inform (input_location,
	    "  when instantiating default argument for call to %D", fn);


  arg = check_default_argument (type, arg, complain);

  pop_access_scope (fn);

  return arg;
}
