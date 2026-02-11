do_free_exception (tree ptr)
{
  tree fn;

  fn = get_identifier ("__cxa_free_exception");
  if (!get_global_value_if_present (fn, &fn))
    {

      fn = push_void_library_fn (fn, tree_cons (NULL_TREE, ptr_type_node,
						void_list_node));
    }

  return build_function_call (fn, tree_cons (NULL_TREE, ptr, NULL_TREE));
}
