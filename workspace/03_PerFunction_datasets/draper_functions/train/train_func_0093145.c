vect_schedule_slp_instance (slp_tree node, slp_instance instance,
                            unsigned int vectorization_factor)
{
  gimple stmt;
  bool grouped_store, is_store;
  gimple_stmt_iterator si;
  stmt_vec_info stmt_info;
  unsigned int vec_stmts_size, nunits, group_size;
  tree vectype;
  int i;
  slp_tree loads_node;
  slp_void_p child;

  if (!node)
    return false;

  FOR_EACH_VEC_ELT (SLP_TREE_CHILDREN (node), i, child)
    vect_schedule_slp_instance ((slp_tree) child, instance,
                                vectorization_factor);

  stmt = SLP_TREE_SCALAR_STMTS (node)[0];
  stmt_info = vinfo_for_stmt (stmt);


  vectype = STMT_VINFO_VECTYPE (stmt_info);
  nunits = (unsigned int) TYPE_VECTOR_SUBPARTS (vectype);
  group_size = SLP_INSTANCE_GROUP_SIZE (instance);


  vec_stmts_size = (vectorization_factor * group_size) / nunits;


  if (SLP_INSTANCE_LOAD_PERMUTATION (instance).exists ())
    {
      FOR_EACH_VEC_ELT (SLP_INSTANCE_LOADS (instance), i, loads_node)
        {
          if (!SLP_TREE_VEC_STMTS (loads_node).exists ())
            {
              SLP_TREE_VEC_STMTS (loads_node).create (vec_stmts_size);
              SLP_TREE_NUMBER_OF_VEC_STMTS (loads_node) = vec_stmts_size;
            }
        }
    }

  if (!SLP_TREE_VEC_STMTS (node).exists ())
    {
      SLP_TREE_VEC_STMTS (node).create (vec_stmts_size);
      SLP_TREE_NUMBER_OF_VEC_STMTS (node) = vec_stmts_size;
    }

  if (dump_enabled_p ())
    {
      dump_printf_loc (MSG_NOTE,vect_location,
		       "------>vectorizing SLP node starting from: ");
      dump_gimple_stmt (MSG_NOTE, TDF_SLIM, stmt, 0);
    }


  if (SLP_INSTANCE_FIRST_LOAD_STMT (instance)
      && STMT_VINFO_GROUPED_ACCESS (stmt_info)
      && !REFERENCE_CLASS_P (gimple_get_lhs (stmt))
      && SLP_INSTANCE_LOAD_PERMUTATION (instance).exists ())
    si = gsi_for_stmt (SLP_INSTANCE_FIRST_LOAD_STMT (instance));
  else if (is_pattern_stmt_p (stmt_info))
    si = gsi_for_stmt (STMT_VINFO_RELATED_STMT (stmt_info));
  else
    si = gsi_for_stmt (stmt);


  if (STMT_VINFO_GROUPED_ACCESS (stmt_info)
      && REFERENCE_CLASS_P (gimple_get_lhs (stmt)))
    {
      gimple last_store = vect_find_last_store_in_slp_instance (instance);
      if (is_pattern_stmt_p (vinfo_for_stmt (last_store)))
       last_store = STMT_VINFO_RELATED_STMT (vinfo_for_stmt (last_store));
      si = gsi_for_stmt (last_store);
    }


  if (GROUP_FIRST_ELEMENT (stmt_info) && !STMT_VINFO_GROUPED_ACCESS (stmt_info)
      && GROUP_FIRST_ELEMENT (stmt_info) == stmt)
    {
      STMT_VINFO_DEF_TYPE (stmt_info) = vect_reduction_def;
      STMT_VINFO_TYPE (stmt_info) = reduc_vec_info_type;
    }

  is_store = vect_transform_stmt (stmt, &si, &grouped_store, node, instance);
  return is_store;
}
