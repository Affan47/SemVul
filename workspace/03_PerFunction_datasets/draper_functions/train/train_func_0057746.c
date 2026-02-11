loop_carried_phi (tree exp)
{
  gimple phi_stmt;
  long block_rank;

  if (TREE_CODE (exp) != SSA_NAME
      || SSA_NAME_IS_DEFAULT_DEF (exp))
    return false;

  phi_stmt = SSA_NAME_DEF_STMT (exp);

  if (gimple_code (SSA_NAME_DEF_STMT (exp)) != GIMPLE_PHI)
    return false;


  block_rank = bb_rank[gimple_bb (phi_stmt)->index];

  if (phi_rank (phi_stmt) != block_rank)
    return true;

  return false;
}
