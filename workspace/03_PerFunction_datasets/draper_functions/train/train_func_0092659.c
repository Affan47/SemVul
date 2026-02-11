eliminate_const_or_copy (gimple stmt, bitmap interesting_names)
{
  tree lhs = get_lhs_or_phi_result (stmt);
  tree rhs;
  int version = SSA_NAME_VERSION (lhs);


  if (has_zero_uses (lhs))
    {
      bitmap_clear_bit (interesting_names, version);
      remove_stmt_or_phi (stmt);
      return;
    }


  rhs = get_rhs_or_phi_arg (stmt);
  if (!rhs)
    {
      bitmap_clear_bit (interesting_names, version);
      return;
    }

  propagate_rhs_into_lhs (stmt, lhs, rhs, interesting_names);


  bitmap_clear_bit (interesting_names, version);
}
