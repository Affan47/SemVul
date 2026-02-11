write_resource_constructor (tree *list_p)
{
  tree decl, t, register_resource_fn;
  unsigned ix;

  if (resources == NULL)
    return;

  t = build_function_type_list (void_type_node, ptr_type_node, NULL);
  t = build_decl (input_location,
		  FUNCTION_DECL, get_identifier ("_Jv_RegisterResource"), t);
  TREE_PUBLIC (t) = 1;
  DECL_EXTERNAL (t) = 1;
  register_resource_fn = t;


  FOR_EACH_VEC_ELT (*resources, ix, decl)
    {
      t = build_fold_addr_expr (decl);
      t = build_call_expr (register_resource_fn, 1, t);
      append_to_statement_list (t, list_p);
    }
}
