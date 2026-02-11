log_tor_version(logfile_t *lf, int reset)
{
  char buf[256];
  size_t n;
  int is_new;

  if (!lf->needs_close)

    return 0;
  if (lf->is_temporary)

    return 0;

  is_new = lf->fd >= 0 && tor_fd_getpos(lf->fd) == 0;

  if (reset && !is_new)


    return 0;
  n = _log_prefix(buf, sizeof(buf), LOG_NOTICE);
  if (appname) {
    tor_snprintf(buf+n, sizeof(buf)-n,
                 "%s opening %slog file.\n", appname, is_new?"new ":"");
  } else {
    tor_snprintf(buf+n, sizeof(buf)-n,
                 "Tor %s opening %slog file.\n", VERSION, is_new?"new ":"");
  }
  if (write_all(lf->fd, buf, strlen(buf), 0) < 0)
    return -1;
  return 0;
}
