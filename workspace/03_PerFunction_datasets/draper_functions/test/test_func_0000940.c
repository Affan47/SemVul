resolve_overloaded_atomic_load (location_t loc, tree function,
				VEC(tree,gc) *params, tree *new_return)
{
  tree p0, p1, p2;
  tree I_type, I_type_ptr;
  int n = get_atomic_generic_size (loc, function, params);


  if (n == 0)
    {
      *new_return = error_mark_node;
      return true;
    }


  if (n != 1 && n != 2 && n != 4 && n != 8 && n != 16)
    {
      *new_return = add_atomic_size_parameter (n, loc, function, params);
      return true;
    }


  p0 = VEC_index (tree, params, 0);
  p1 = VEC_index (tree, params, 1);
  p2 = VEC_index (tree, params, 2);


  I_type = builtin_type_for_size (BITS_PER_UNIT * n, 1);
  I_type_ptr = build_pointer_type (I_type);


  p0 = build1 (VIEW_CONVERT_EXPR, I_type_ptr, p0);
  VEC_replace (tree, params, 0, p0);


  VEC_replace (tree, params, 1, p2);
  VEC_truncate (tree, params, 2);


  *new_return = build_indirect_ref (loc, p1, RO_UNARY_STAR);

  return false;
}
