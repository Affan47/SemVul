maybe_clean_eh_stmt_fn (struct function *ifun, gimple stmt)
{
  if (stmt_could_throw_p (stmt))
    return false;
  return remove_stmt_from_eh_lp_fn (ifun, stmt);
}
