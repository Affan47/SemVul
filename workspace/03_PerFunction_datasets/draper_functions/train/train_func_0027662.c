format_garmin_xt_read(void)
{

  if (strcmp(opt_xt_ftype, "STRK") == 0) {
    format_garmin_xt_proc_strk();
  } else {
    format_garmin_xt_proc_atrk();
  }
}
