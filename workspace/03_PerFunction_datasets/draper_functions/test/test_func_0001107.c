normalize_cond_1 (gimple cond,
                  norm_cond_t norm_cond,
                  enum tree_code cond_code)
{
  enum gimple_code gc;
  enum tree_code cur_cond_code;
  tree rhs1, rhs2;

  gc = gimple_code (cond);
  if (gc != GIMPLE_ASSIGN)
    {
      norm_cond->conds.safe_push (cond);
      return;
    }

  cur_cond_code = gimple_assign_rhs_code (cond);
  rhs1 = gimple_assign_rhs1 (cond);
  rhs2 = gimple_assign_rhs2 (cond);
  if (cur_cond_code == NE_EXPR)
    {
      if (integer_zerop (rhs2)
          && (TREE_CODE (rhs1) == SSA_NAME))
        normalize_cond_1 (
            SSA_NAME_DEF_STMT (rhs1),
            norm_cond, cond_code);
      else if (integer_zerop (rhs1)
               && (TREE_CODE (rhs2) == SSA_NAME))
        normalize_cond_1 (
            SSA_NAME_DEF_STMT (rhs2),
            norm_cond, cond_code);
      else
        norm_cond->conds.safe_push (cond);

      return;
    }

  if (is_and_or_or (cur_cond_code, TREE_TYPE (rhs1))
      && (cond_code == cur_cond_code || cond_code == ERROR_MARK)
      && (TREE_CODE (rhs1) == SSA_NAME && TREE_CODE (rhs2) == SSA_NAME))
    {
      normalize_cond_1 (SSA_NAME_DEF_STMT (rhs1),
                        norm_cond, cur_cond_code);
      normalize_cond_1 (SSA_NAME_DEF_STMT (rhs2),
                        norm_cond, cur_cond_code);
      norm_cond->cond_code = cur_cond_code;
    }
  else
    norm_cond->conds.safe_push (cond);
}
