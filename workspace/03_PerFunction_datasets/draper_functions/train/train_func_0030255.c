run_fast_df_dce (void)
{
  if (flag_dce)
    {


      int old_flags =
	df_clear_flags (DF_DEFER_INSN_RESCAN + DF_NO_INSN_RESCAN);

      df_in_progress = true;
      rest_of_handle_fast_dce ();
      df_in_progress = false;

      df_set_flags (old_flags);
    }
}
