execute_rtl_hoist (void)
{
  int changed;
  delete_unreachable_blocks ();
  df_analyze ();
  changed = one_code_hoisting_pass ();
  flag_rerun_cse_after_global_opts |= changed;
  if (changed)
    cleanup_cfg (0);
  return 0;
}
