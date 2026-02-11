rep_hist_format_router_status(or_history_t *hist, time_t now)
{
  char sor_buf[ISO_TIME_LEN+1];
  char sod_buf[ISO_TIME_LEN+1];
  double wfu;
  double mtbf;
  int up = 0, down = 0;
  char *cp = NULL;

  if (hist->start_of_run) {
    format_iso_time(sor_buf, hist->start_of_run);
    up = 1;
  }
  if (hist->start_of_downtime) {
    format_iso_time(sod_buf, hist->start_of_downtime);
    down = 1;
  }

  wfu = get_weighted_fractional_uptime(hist, now);
  mtbf = get_stability(hist, now);
  tor_asprintf(&cp,
               "%s%s%s"
               "%s%s%s"
               "wfu %0.3lf\n"
               " weighted-time %lu\n"
               " weighted-uptime %lu\n"
               "mtbf %0.1lf\n"
               " weighted-run-length %lu\n"
               " total-run-weights %f\n",
               up?"uptime-started ":"", up?sor_buf:"", up?" UTC\n":"",
               down?"downtime-started ":"", down?sod_buf:"", down?" UTC\n":"",
               wfu,
               hist->total_weighted_time,
               hist->weighted_uptime,
               mtbf,
               hist->weighted_run_length,
               hist->total_run_weights
               );
  return cp;
}
