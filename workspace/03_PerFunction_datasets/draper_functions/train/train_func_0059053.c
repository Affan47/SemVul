optimize_double_finally (gimple one, gimple two)
{
  gimple oneh;
  gimple_stmt_iterator gsi;
  gimple_seq cleanup;

  cleanup = gimple_try_cleanup (one);
  gsi = gsi_start (cleanup);
  if (!gsi_one_before_end_p (gsi))
    return;

  oneh = gsi_stmt (gsi);
  if (gimple_code (oneh) != GIMPLE_TRY
      || gimple_try_kind (oneh) != GIMPLE_TRY_CATCH)
    return;

  if (same_handler_p (gimple_try_cleanup (oneh), gimple_try_cleanup (two)))
    {
      gimple_seq seq = gimple_try_eval (oneh);

      gimple_try_set_cleanup (one, seq);
      gimple_try_set_kind (one, GIMPLE_TRY_CATCH);
      seq = copy_gimple_seq_and_replace_locals (seq);
      gimple_seq_add_seq (&seq, gimple_try_eval (two));
      gimple_try_set_eval (two, seq);
    }
}
