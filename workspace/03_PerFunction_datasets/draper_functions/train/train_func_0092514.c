default_add_stmt_cost (void *data, int count, enum vect_cost_for_stmt kind,
		       struct _stmt_vec_info *stmt_info, int misalign,
		       enum vect_cost_model_location where)
{
  unsigned *cost = (unsigned *) data;
  unsigned retval = 0;

  tree vectype = stmt_info ? stmt_vectype (stmt_info) : NULL_TREE;
  int stmt_cost = default_builtin_vectorization_cost (kind, vectype,
							  misalign);


  if (where == vect_body && stmt_info && stmt_in_inner_loop_p (stmt_info))
    count *= 50;

  retval = (unsigned) (count * stmt_cost);
  cost[where] += retval;

  return retval;
}
