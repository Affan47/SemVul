build_logfile_path(char *buf, const int buf_len)
{
  char	*bounds_p;
  char	*path_p, *buf_p, *start_p;
  int	len;

  if (dmalloc_logpath == NULL) {
    buf[0] = '\0';
    return;
  }

  buf_p = buf;
  bounds_p = buf + buf_len;

  start_p = dmalloc_logpath;
  for (path_p = dmalloc_logpath; *path_p != '\0'; path_p++) {


    if (*path_p != '%' || *(path_p + 1) == '\0') {
      if (buf_p < bounds_p) {
	*buf_p++ = *path_p;
      }
      continue;
    }


    path_p++;


    if (*path_p == 'h') {
#if HAVE_GETHOSTNAME
      char	our_host[128];
      gethostname(our_host, sizeof(our_host));
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "%s", our_host);
#else
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "not-gethostname");
#endif
    }

    if (*path_p == 'i') {
#if LOG_PNT_THREAD_ID
      char		id_str[256];
      THREAD_TYPE	id;

      id = THREAD_GET_ID();
      THREAD_ID_TO_STRING(id_str, sizeof(id_str), id);
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "%s", id_str);
#else
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "no-thread-id");
#endif
    }

    if (*path_p == 'p' || *path_p == 'd') {
#if HAVE_GETPID

      long	our_pid = getpid();
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "%ld", our_pid);
#else
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "no-getpid");
#endif
    }

    if (*path_p == 't') {
#if HAVE_TIME

      long	now;
      now = time(NULL);
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "%ld", now);
#else
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "no-time");
#endif
    }

    if (*path_p == 'u') {
#if HAVE_GETUID

      long	our_uid = getuid();
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "%ld", our_uid);
#else
      buf_p += loc_snprintf(buf_p, bounds_p - buf_p, "no-uid");
#endif
    }
  }

  if (buf_p >= bounds_p - 1) {

    len = loc_snprintf(error_str, sizeof(error_str),
		       "debug-malloc library: logfile path too large '%s'\r\n",
		       dmalloc_logpath);
    (void)write(STDERR, error_str, len);
  }

  *buf_p = '\0';
}
