build_tm_store (location_t loc, tree lhs, tree rhs, gimple_stmt_iterator *gsi)
{
  enum built_in_function code = END_BUILTINS;
  tree t, fn, type = TREE_TYPE (rhs), simple_type;
  gimple gcall;

  if (type == float_type_node)
    code = BUILT_IN_TM_STORE_FLOAT;
  else if (type == double_type_node)
    code = BUILT_IN_TM_STORE_DOUBLE;
  else if (type == long_double_type_node)
    code = BUILT_IN_TM_STORE_LDOUBLE;
  else if (TYPE_SIZE_UNIT (type) != NULL
	   && host_integerp (TYPE_SIZE_UNIT (type), 1))
    {
      switch (tree_low_cst (TYPE_SIZE_UNIT (type), 1))
	{
	case 1:
	  code = BUILT_IN_TM_STORE_1;
	  break;
	case 2:
	  code = BUILT_IN_TM_STORE_2;
	  break;
	case 4:
	  code = BUILT_IN_TM_STORE_4;
	  break;
	case 8:
	  code = BUILT_IN_TM_STORE_8;
	  break;
	}
    }

  if (code == END_BUILTINS)
    {
      fn = targetm.vectorize.builtin_tm_store (type);
      if (!fn)
	return NULL;
    }
  else
    fn = builtin_decl_explicit (code);

  simple_type = TREE_VALUE (TREE_CHAIN (TYPE_ARG_TYPES (TREE_TYPE (fn))));

  if (TREE_CODE (rhs) == CONSTRUCTOR)
    {

      if (!CONSTRUCTOR_ELTS (rhs))
	rhs = build_int_cst (simple_type, 0);
      else
	{


	  return NULL;
	}
    }
  else if (!useless_type_conversion_p (simple_type, type))
    {
      gimple g;
      tree temp;

      temp = create_tmp_reg (simple_type, NULL);
      t = fold_build1 (VIEW_CONVERT_EXPR, simple_type, rhs);
      g = gimple_build_assign (temp, t);
      gimple_set_location (g, loc);
      gsi_insert_before (gsi, g, GSI_SAME_STMT);

      rhs = temp;
    }

  t = gimplify_addr (gsi, lhs);
  gcall = gimple_build_call (fn, 2, t, rhs);
  gimple_set_location (gcall, loc);
  gsi_insert_before (gsi, gcall, GSI_SAME_STMT);

  return gcall;
}
