fterr_warnx(const char *fmt, ...)
{
  va_list ap;
  char buf[1025];
  char buf2[1025];

  va_start(ap, fmt);
  vsnprintf(buf, (size_t)1024, fmt, ap);
  va_end(ap);

  if (fterr_flags & FTERR_FILE) {
    snprintf(buf2, 1024, "%s: %s", fterr_id, buf);
    fprintf(((fterr_file) ? fterr_file : stderr), "%s\n", buf2);
  }

  if (fterr_flags & FTERR_SYSLOG)
    syslog(LOG_INFO, buf);

}
