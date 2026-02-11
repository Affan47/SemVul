vect_get_vec_defs_for_stmt_copy (enum vect_def_type *dt,
				 vec<tree> *vec_oprnds0,
				 vec<tree> *vec_oprnds1)
{
  tree vec_oprnd = vec_oprnds0->pop ();

  vec_oprnd = vect_get_vec_def_for_stmt_copy (dt[0], vec_oprnd);
  vec_oprnds0->quick_push (vec_oprnd);

  if (vec_oprnds1 && vec_oprnds1->length ())
    {
      vec_oprnd = vec_oprnds1->pop ();
      vec_oprnd = vect_get_vec_def_for_stmt_copy (dt[1], vec_oprnd);
      vec_oprnds1->quick_push (vec_oprnd);
    }
}
