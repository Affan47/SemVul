vect_get_vec_defs_for_stmt_copy (enum vect_def_type *dt,
				 VEC(tree,heap) **vec_oprnds0,
				 VEC(tree,heap) **vec_oprnds1)
{
  tree vec_oprnd = VEC_pop (tree, *vec_oprnds0);

  vec_oprnd = vect_get_vec_def_for_stmt_copy (dt[0], vec_oprnd);
  VEC_quick_push (tree, *vec_oprnds0, vec_oprnd);

  if (vec_oprnds1 && *vec_oprnds1)
    {
      vec_oprnd = VEC_pop (tree, *vec_oprnds1);
      vec_oprnd = vect_get_vec_def_for_stmt_copy (dt[1], vec_oprnd);
      VEC_quick_push (tree, *vec_oprnds1, vec_oprnd);
    }
}
