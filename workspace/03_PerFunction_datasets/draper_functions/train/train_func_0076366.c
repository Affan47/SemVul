set_max_file_descriptors(rlim_t limit, int *max_out)
{


#ifndef HAVE_GETRLIMIT
#if defined(CYGWIN) || defined(__CYGWIN__)
  const char *platform = "Cygwin";
  const unsigned long MAX_CONNECTIONS = 3200;
#elif defined(_WIN32)
  const char *platform = "Windows";
  const unsigned long MAX_CONNECTIONS = 15000;
#else
  const char *platform = "unknown platforms with no getrlimit()";
  const unsigned long MAX_CONNECTIONS = 15000;
#endif
  log_fn(LOG_INFO, LD_NET,
         "This platform is missing getrlimit(). Proceeding.");
  if (limit > MAX_CONNECTIONS) {
    log_warn(LD_CONFIG,
             "We do not support more than %lu file descriptors "
             "on %s. Tried to raise to %lu.",
             (unsigned long)MAX_CONNECTIONS, platform, (unsigned long)limit);
    return -1;
  }
  limit = MAX_CONNECTIONS;
#else
  struct rlimit rlim;
  tor_assert(limit > 0);

  if (getrlimit(RLIMIT_NOFILE, &rlim) != 0) {
    log_warn(LD_NET, "Could not get maximum number of file descriptors: %s",
             strerror(errno));
    return -1;
  }

  if (rlim.rlim_max < limit) {
    log_warn(LD_CONFIG,"We need %lu file descriptors available, and we're "
             "limited to %lu. Please change your ulimit -n.",
             (unsigned long)limit, (unsigned long)rlim.rlim_max);
    return -1;
  }

  if (rlim.rlim_max > rlim.rlim_cur) {
    log_info(LD_NET,"Raising max file descriptors from %lu to %lu.",
             (unsigned long)rlim.rlim_cur, (unsigned long)rlim.rlim_max);
  }
  rlim.rlim_cur = rlim.rlim_max;

  if (setrlimit(RLIMIT_NOFILE, &rlim) != 0) {
    int bad = 1;
#ifdef OPEN_MAX
    if (errno == EINVAL && OPEN_MAX < rlim.rlim_cur) {


      rlim.rlim_cur = OPEN_MAX;
      if (setrlimit(RLIMIT_NOFILE, &rlim) == 0) {
        if (rlim.rlim_cur < (rlim_t)limit) {
          log_warn(LD_CONFIG, "We are limited to %lu file descriptors by "
                 "OPEN_MAX, and ConnLimit is %lu.  Changing ConnLimit; sorry.",
                   (unsigned long)OPEN_MAX, (unsigned long)limit);
        } else {
          log_info(LD_CONFIG, "Dropped connection limit to OPEN_MAX (%lu); "
                   "Apparently, %lu was too high and rlimit lied to us.",
                   (unsigned long)OPEN_MAX, (unsigned long)rlim.rlim_max);
        }
        bad = 0;
      }
    }
#endif
    if (bad) {
      log_warn(LD_CONFIG,"Couldn't set maximum number of file descriptors: %s",
               strerror(errno));
      return -1;
    }
  }

  limit = rlim.rlim_cur;
#endif

  if (limit < ULIMIT_BUFFER) {
    log_warn(LD_CONFIG,
             "ConnLimit must be at least %d. Failing.", ULIMIT_BUFFER);
    return -1;
  }
  if (limit > INT_MAX)
    limit = INT_MAX;
  tor_assert(max_out);
  *max_out = (int)limit - ULIMIT_BUFFER;
  return 0;
}
