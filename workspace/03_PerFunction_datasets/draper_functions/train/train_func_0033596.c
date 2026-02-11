default_hidden_stack_protect_fail (void)
{
#ifndef HAVE_GAS_HIDDEN
  return default_external_stack_protect_fail ();
#else
  tree t = stack_chk_fail_decl;

  if (!flag_pic)
    return default_external_stack_protect_fail ();

  if (t == NULL_TREE)
    {
      t = build_function_type_list (void_type_node, NULL_TREE);
      t = build_decl (UNKNOWN_LOCATION, FUNCTION_DECL,
		      get_identifier ("__stack_chk_fail_local"), t);
      TREE_STATIC (t) = 1;
      TREE_PUBLIC (t) = 1;
      DECL_EXTERNAL (t) = 1;
      TREE_USED (t) = 1;
      TREE_THIS_VOLATILE (t) = 1;
      TREE_NOTHROW (t) = 1;
      DECL_ARTIFICIAL (t) = 1;
      DECL_IGNORED_P (t) = 1;
      DECL_VISIBILITY_SPECIFIED (t) = 1;
      DECL_VISIBILITY (t) = VISIBILITY_HIDDEN;

      stack_chk_fail_decl = t;
    }

  return build_call_expr (t, 0);
#endif
}
