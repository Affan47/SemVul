change_callback_log_severity(int loglevelMin, int loglevelMax,
                             log_callback cb)
{
  logfile_t *lf;
  log_severity_list_t severities;
  set_log_severity_config(loglevelMin, loglevelMax, &severities);
  LOCK_LOGS();
  for (lf = logfiles; lf; lf = lf->next) {
    if (lf->callback == cb) {
      memcpy(lf->severities, &severities, sizeof(severities));
    }
  }
  _log_global_min_severity = get_min_log_level();
  UNLOCK_LOGS();
}
