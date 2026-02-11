check_pow (gimple pow_call)
{
  tree base, expn;
  enum tree_code bc, ec;

  if (gimple_call_num_args (pow_call) != 2)
    return false;

  base = gimple_call_arg (pow_call, 0);
  expn = gimple_call_arg (pow_call, 1);

  if (!check_target_format (expn))
    return false;

  bc = TREE_CODE (base);
  ec = TREE_CODE (expn);


  if (ec == REAL_CST && bc == REAL_CST)
    return false;

  if (bc == REAL_CST)
    {

      REAL_VALUE_TYPE mv;
      REAL_VALUE_TYPE bcv = TREE_REAL_CST (base);
      if (REAL_VALUES_EQUAL (bcv, dconst1))
        return false;
      if (REAL_VALUES_LESS (bcv, dconst1))
        return false;
      real_from_integer (&mv, TYPE_MODE (TREE_TYPE (base)), 256, 0, 1);
      if (REAL_VALUES_LESS (mv, bcv))
        return false;
      return true;
    }
  else if (bc == SSA_NAME)
    {
      tree base_val0, base_var, type;
      gimple base_def;
      int bit_sz;


      base_def = SSA_NAME_DEF_STMT (base);
      if (gimple_code (base_def) != GIMPLE_ASSIGN)
        return false;

      if (gimple_assign_rhs_code (base_def) != FLOAT_EXPR)
        return false;
      base_val0 = gimple_assign_rhs1 (base_def);

      base_var = SSA_NAME_VAR (base_val0);
      if (!DECL_P  (base_var))
        return false;

      type = TREE_TYPE (base_var);
      if (TREE_CODE (type) != INTEGER_TYPE)
        return false;
      bit_sz = TYPE_PRECISION (type);


      if (bit_sz > MAX_BASE_INT_BIT_SIZE)
        return false;

      return true;
    }
  else
    return false;
}
