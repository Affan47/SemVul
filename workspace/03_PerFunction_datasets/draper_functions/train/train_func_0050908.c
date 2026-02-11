finish_function (void)
{
  tree fndecl = current_function_decl;

  if (c_dialect_objc ())
    objc_finish_function ();

  if (TREE_CODE (fndecl) == FUNCTION_DECL
      && targetm.calls.promote_prototypes (TREE_TYPE (fndecl)))
    {
      tree args = DECL_ARGUMENTS (fndecl);
      for (; args; args = DECL_CHAIN (args))
	{
	  tree type = TREE_TYPE (args);
	  if (INTEGRAL_TYPE_P (type)
	      && TYPE_PRECISION (type) < TYPE_PRECISION (integer_type_node))
	    DECL_ARG_TYPE (args) = integer_type_node;
	}
    }

  if (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_node)
    BLOCK_SUPERCONTEXT (DECL_INITIAL (fndecl)) = fndecl;


  if (DECL_RESULT (fndecl) && DECL_RESULT (fndecl) != error_mark_node)
    DECL_CONTEXT (DECL_RESULT (fndecl)) = fndecl;

  if (MAIN_NAME_P (DECL_NAME (fndecl)) && flag_hosted
      && TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (fndecl)))
      == integer_type_node && flag_isoc99)
    {


      c_finish_return (BUILTINS_LOCATION, integer_zero_node, NULL_TREE);
    }


  DECL_SAVED_TREE (fndecl) = pop_stmt_list (DECL_SAVED_TREE (fndecl));

  finish_fname_decls ();


  if (warn_return_type
      && TREE_CODE (TREE_TYPE (TREE_TYPE (fndecl))) != VOID_TYPE
      && !current_function_returns_value && !current_function_returns_null

      && !current_function_returns_abnormally

      && !TREE_THIS_VOLATILE (fndecl)

      && !MAIN_NAME_P (DECL_NAME (fndecl))

      && !C_FUNCTION_IMPLICIT_INT (fndecl)


      && !TREE_PUBLIC (fndecl))
    {
      warning (OPT_Wreturn_type,
	       "no return statement in function returning non-void");
      TREE_NO_WARNING (fndecl) = 1;
    }


  if (warn_unused_but_set_parameter)
    {
      tree decl;

      for (decl = DECL_ARGUMENTS (fndecl);
	   decl;
	   decl = DECL_CHAIN (decl))
	if (TREE_USED (decl)
	    && TREE_CODE (decl) == PARM_DECL
	    && !DECL_READ_P (decl)
	    && DECL_NAME (decl)
	    && !DECL_ARTIFICIAL (decl)
	    && !TREE_NO_WARNING (decl))
	  warning_at (DECL_SOURCE_LOCATION (decl),
		      OPT_Wunused_but_set_parameter,
		      "parameter %qD set but not used", decl);
    }


  maybe_warn_unused_local_typedefs ();


  cfun->function_end_locus = input_location;


  c_determine_visibility (fndecl);


  if (DECL_EXTERNAL (fndecl)
      && DECL_DECLARED_INLINE_P (fndecl))
    DECL_DISREGARD_INLINE_LIMITS (fndecl) = 1;


  if (DECL_INITIAL (fndecl) && DECL_INITIAL (fndecl) != error_mark_node
      && !undef_nested_function)
    {
      if (!decl_function_context (fndecl))
	{
	  invoke_plugin_callbacks (PLUGIN_PRE_GENERICIZE, fndecl);
	  c_genericize (fndecl);


	  if (cgraph_global_info_ready)
	    {
	      cgraph_add_new_function (fndecl, false);
	      return;
	    }
	  cgraph_finalize_function (fndecl, false);
	}
      else
	{


	  (void) cgraph_get_create_node (fndecl);
	}
    }

  if (!decl_function_context (fndecl))
    undef_nested_function = false;

  if (cfun->language != NULL)
    {
      ggc_free (cfun->language);
      cfun->language = NULL;
    }


  set_cfun (NULL);
  current_function_decl = NULL;
}
