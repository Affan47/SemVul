control_event_bootstrap(bootstrap_status_t status, int progress)
{
  const char *tag, *summary;
  char buf[BOOTSTRAP_MSG_LEN];

  if (bootstrap_percent == BOOTSTRAP_STATUS_DONE)
    return;


  if (status == BOOTSTRAP_STATUS_HANDSHAKE) {
    if (bootstrap_percent < BOOTSTRAP_STATUS_CONN_OR) {
      status =  BOOTSTRAP_STATUS_HANDSHAKE_DIR;
    } else {
      status = BOOTSTRAP_STATUS_HANDSHAKE_OR;
    }
  }

  if (status > bootstrap_percent ||
      (progress && progress > bootstrap_percent)) {
    bootstrap_status_to_string(status, &tag, &summary);
    log(status ? LOG_NOTICE : LOG_INFO, LD_CONTROL,
        "Bootstrapped %d%%: %s.", progress ? progress : status, summary);
    tor_snprintf(buf, sizeof(buf),
        "BOOTSTRAP PROGRESS=%d TAG=%s SUMMARY=\"%s\"",
        progress ? progress : status, tag, summary);
    tor_snprintf(last_sent_bootstrap_message,
                 sizeof(last_sent_bootstrap_message),
                 "NOTICE %s", buf);
    control_event_client_status(LOG_NOTICE, "%s", buf);
    if (status > bootstrap_percent) {
      bootstrap_percent = status;
    }
    if (progress > bootstrap_percent) {

      bootstrap_percent = progress;
      bootstrap_problems = 0;
    }
  }
}
