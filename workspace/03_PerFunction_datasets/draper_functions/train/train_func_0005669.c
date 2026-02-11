handle_relock_after_trim(void)
{
  int valid;
  time_t ref;
  double fast, slope;

  run_regression(1, &valid, &ref, &fast, &slope);

  if (valid) {
    write_coefs_to_file(1,ref,fast,saved_coef_gain_rate);
  } else {
    LOG(LOGS_WARN, LOGF_RtcLinux, "Could not do regression after trim");
  }

  coefs_valid = 0;
  n_samples = 0;
  n_samples_since_regression = 0;
  operating_mode = OM_NORMAL;
  measurement_period = LOWEST_MEASUREMENT_PERIOD;
}
