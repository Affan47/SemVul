do_while_loop_p (struct loop *loop)
{
  gimple stmt = last_stmt (loop->latch);


  if (stmt
      && gimple_code (stmt) != GIMPLE_LABEL)
    return false;


  stmt = last_and_only_stmt (loop->header);
  if (stmt
      && gimple_code (stmt) == GIMPLE_COND)
    return false;

  return true;
}
