var_at_stmt (struct loop *loop, struct iv_cand *cand, gimple stmt)
{
  if (stmt_after_increment (loop, cand, stmt))
    return cand->var_after;
  else
    return cand->var_before;
}
