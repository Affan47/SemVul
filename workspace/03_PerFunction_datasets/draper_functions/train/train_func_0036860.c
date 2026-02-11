build_function_call (location_t loc, tree function, tree params)
{
  vec<tree, va_gc> *v;
  tree ret;

  vec_alloc (v, list_length (params));
  for (; params; params = TREE_CHAIN (params))
    v->quick_push (TREE_VALUE (params));
  ret = c_build_function_call_vec (loc, function, v, NULL);
  vec_free (v);
  return ret;
}
