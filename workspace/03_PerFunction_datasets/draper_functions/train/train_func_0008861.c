stmt_has_constants (gimple stmt)
{
  if (gimple_code (stmt) != GIMPLE_ASSIGN)
    return false;

  switch (get_gimple_rhs_class (gimple_assign_rhs_code (stmt)))
    {
    case GIMPLE_UNARY_RHS:
      return is_gimple_min_invariant (gimple_assign_rhs1 (stmt));

    case GIMPLE_BINARY_RHS:
      return (is_gimple_min_invariant (gimple_assign_rhs1 (stmt))
	      || is_gimple_min_invariant (gimple_assign_rhs2 (stmt)));
    case GIMPLE_TERNARY_RHS:
      return (is_gimple_min_invariant (gimple_assign_rhs1 (stmt))
	      || is_gimple_min_invariant (gimple_assign_rhs2 (stmt))
	      || is_gimple_min_invariant (gimple_assign_rhs3 (stmt)));
    case GIMPLE_SINGLE_RHS:


      return is_gimple_min_invariant (gimple_assign_rhs1 (stmt));
    default:
      gcc_unreachable ();
    }
  return false;
}
