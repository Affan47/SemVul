format_time_duration(time_t t, char *buf, int maxlen)
{
  int seconds, minutes, hours, days;
  bool space = FALSE;

  seconds = t % 60;
  minutes = (t / 60) % 60;
  hours = (t / (60 * 60)) % 24;
  days = t / (60 * 60 * 24);

  if (maxlen <= 0) {
    return;
  }

  buf[0] = '\0';

  if (days > 0) {
    cat_snprintf(buf, maxlen, "%d %s", days, PL_("day", "days", days));
    space = TRUE;
  }
  if (hours > 0) {
    cat_snprintf(buf, maxlen, "%s%d %s",
                 space ? " " : "", hours, PL_("hour", "hours", hours));
    space = TRUE;
  }
  if (minutes > 0) {
    cat_snprintf(buf, maxlen, "%s%d %s",
                 space ? " " : "",
                 minutes, PL_("minute", "minutes", minutes));
    space = TRUE;
  }
  if (seconds > 0) {
    cat_snprintf(buf, maxlen, "%s%d %s",
                 space ? " " : "",
                 seconds, PL_("second", "seconds", seconds));
  }
}
