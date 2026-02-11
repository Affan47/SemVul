add_atomic_size_parameter (unsigned n, location_t loc, tree function,
			   VEC(tree,gc) *params)
{
  tree size_node;


  if (!VEC_space (tree, params, 1))
    {
      unsigned int z, len;
      VEC(tree,gc) *vec;
      tree f;

      len = VEC_length (tree, params);
      vec = VEC_alloc (tree, gc, len + 1);
      for (z = 0; z < len; z++)
	VEC_quick_push (tree, vec, VEC_index (tree, params, z));
      f = build_function_call_vec (loc, function, vec, NULL);
      VEC_free (tree, gc, vec);
      return f;
    }


  size_node = build_int_cst (size_type_node, n);
  VEC_quick_insert (tree, params, 0, size_node);
  return NULL_TREE;
}
