stmt_overflow_infinity (gimple stmt)
{
  if (is_gimple_assign (stmt)
      && get_gimple_rhs_class (gimple_assign_rhs_code (stmt)) ==
      GIMPLE_SINGLE_RHS)
    return is_overflow_infinity (gimple_assign_rhs1 (stmt));
  return false;
}
