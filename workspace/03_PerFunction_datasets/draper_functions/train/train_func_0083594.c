get_rhs_or_phi_arg (gimple stmt)
{
  if (gimple_code (stmt) == GIMPLE_PHI)
    return degenerate_phi_result (stmt);
  else if (gimple_assign_single_p (stmt))
    return gimple_assign_rhs1 (stmt);
  else
    gcc_unreachable ();
}
