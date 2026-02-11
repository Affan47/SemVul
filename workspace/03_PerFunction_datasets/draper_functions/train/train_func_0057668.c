reginfo_init (void)
{
  if (df)
    df_compute_regs_ever_live (true);


  reg_pref = NULL;
  reg_info_size = max_regno_since_last_resize = 0;

  no_global_reg_vars = 1;
  return 1;
}
