defcodefor_name (tree name, enum tree_code *code, tree *arg1, tree *arg2)
{
  gimple def;
  enum tree_code code1;
  tree arg11;
  tree arg21;
  tree arg31;
  enum gimple_rhs_class grhs_class;

  code1 = TREE_CODE (name);
  arg11 = name;
  arg21 = NULL_TREE;
  grhs_class = get_gimple_rhs_class (code1);

  if (code1 == SSA_NAME)
    {
      def = SSA_NAME_DEF_STMT (name);

      if (def && is_gimple_assign (def)
	  && can_propagate_from (def))
	{
	  code1 = gimple_assign_rhs_code (def);
	  arg11 = gimple_assign_rhs1 (def);
          arg21 = gimple_assign_rhs2 (def);
          arg31 = gimple_assign_rhs2 (def);
	}
    }
  else if (grhs_class == GIMPLE_TERNARY_RHS
	   || GIMPLE_BINARY_RHS
	   || GIMPLE_UNARY_RHS
	   || GIMPLE_SINGLE_RHS)
    extract_ops_from_tree_1 (name, &code1, &arg11, &arg21, &arg31);

  *code = code1;
  *arg1 = arg11;
  if (arg2)
    *arg2 = arg21;

}
