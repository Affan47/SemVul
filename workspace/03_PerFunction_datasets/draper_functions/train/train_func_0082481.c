stmt_may_generate_copy (gimple stmt)
{
  if (gimple_code (stmt) == GIMPLE_PHI)
    return !SSA_NAME_OCCURS_IN_ABNORMAL_PHI (gimple_phi_result (stmt));

  if (gimple_code (stmt) != GIMPLE_ASSIGN)
    return false;


  if (gimple_has_volatile_ops (stmt))
    return false;


  if (gimple_vuse (stmt))
    return false;


  return ((gimple_assign_rhs_code (stmt) == SSA_NAME
	   && !SSA_NAME_OCCURS_IN_ABNORMAL_PHI (gimple_assign_rhs1 (stmt)))
	  || is_gimple_min_invariant (gimple_assign_rhs1 (stmt)));
}
