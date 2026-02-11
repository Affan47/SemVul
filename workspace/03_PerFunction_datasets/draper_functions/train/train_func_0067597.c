logerror (const char *type)
{
  char buf[100];

  if (errno)
    snprintf (buf, sizeof (buf), "syslogd: %s: %s", type, strerror (errno));
  else
    snprintf (buf, sizeof (buf), "syslogd: %s", type);
  errno = 0;
  dbg_printf ("%s\n", buf);
  logmsg (LOG_SYSLOG | LOG_ERR, buf, LocalHostName, ADDDATE);
}
