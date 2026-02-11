vect_schedule_slp_instance (slp_tree node, slp_instance instance,
                            unsigned int vectorization_factor)
{
  gimple stmt;
  bool strided_store, is_store;
  gimple_stmt_iterator si;
  stmt_vec_info stmt_info;
  unsigned int vec_stmts_size, nunits, group_size;
  tree vectype;
  int i;
  slp_tree loads_node;
  slp_void_p child;

  if (!node)
    return false;

  FOR_EACH_VEC_ELT (slp_void_p, SLP_TREE_CHILDREN (node), i, child)
    vect_schedule_slp_instance ((slp_tree) child, instance,
                                vectorization_factor);

  stmt = VEC_index (gimple, SLP_TREE_SCALAR_STMTS (node), 0);
  stmt_info = vinfo_for_stmt (stmt);


  vectype = STMT_VINFO_VECTYPE (stmt_info);
  nunits = (unsigned int) TYPE_VECTOR_SUBPARTS (vectype);
  group_size = SLP_INSTANCE_GROUP_SIZE (instance);


  vec_stmts_size = (vectorization_factor * group_size) / nunits;


  if (SLP_INSTANCE_LOAD_PERMUTATION (instance))
    {
      FOR_EACH_VEC_ELT (slp_tree, SLP_INSTANCE_LOADS (instance), i, loads_node)
        {
          if (!SLP_TREE_VEC_STMTS (loads_node))
            {
              SLP_TREE_VEC_STMTS (loads_node) = VEC_alloc (gimple, heap,
                                                           vec_stmts_size);
              SLP_TREE_NUMBER_OF_VEC_STMTS (loads_node) = vec_stmts_size;
            }
        }
    }

  if (!SLP_TREE_VEC_STMTS (node))
    {
      SLP_TREE_VEC_STMTS (node) = VEC_alloc (gimple, heap, vec_stmts_size);
      SLP_TREE_NUMBER_OF_VEC_STMTS (node) = vec_stmts_size;
    }

  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "------>vectorizing SLP node starting from: ");
      print_gimple_stmt (vect_dump, stmt, 0, TDF_SLIM);
    }


  if (SLP_INSTANCE_FIRST_LOAD_STMT (instance)
      && STMT_VINFO_STRIDED_ACCESS (stmt_info)
      && !REFERENCE_CLASS_P (gimple_get_lhs (stmt))
      && SLP_INSTANCE_LOAD_PERMUTATION (instance))
    si = gsi_for_stmt (SLP_INSTANCE_FIRST_LOAD_STMT (instance));
  else if (is_pattern_stmt_p (stmt_info))
    si = gsi_for_stmt (STMT_VINFO_RELATED_STMT (stmt_info));
  else
    si = gsi_for_stmt (stmt);


  if (STMT_VINFO_STRIDED_ACCESS (stmt_info)
      && REFERENCE_CLASS_P (gimple_get_lhs (stmt)))
    {
      gimple last_store = vect_find_last_store_in_slp_instance (instance);
      si = gsi_for_stmt (last_store);
    }

  is_store = vect_transform_stmt (stmt, &si, &strided_store, node, instance);
  return is_store;
}
