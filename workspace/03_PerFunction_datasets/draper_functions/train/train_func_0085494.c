print_total_time(const ESL_GETOPTS *go, double total_asec, double total_psec)
{
  char  time_buf[128];

  printf("# %20s  %12s", "--------------------", "------------");
  if(! esl_opt_IsUsed(go, "--forecast")) {
    FormatTimeString(time_buf, total_asec, FALSE);
    printf("  %42s  %12s", "------------------------------------------", "------------");
  }
  printf("\n");
  FormatTimeString(time_buf, total_psec, FALSE);
  printf("# %-20s  %12s", "all models", time_buf);
  if(! esl_opt_IsUsed(go, "--forecast")) {
    FormatTimeString(time_buf, total_asec, FALSE);
    printf("  %42s  %12s", "", time_buf);
  }
  printf("\n");

  return;
}
