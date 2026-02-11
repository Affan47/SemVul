get_max_fds (void)
{
  int max_fds = -1;
#ifdef HAVE_GETRLIMIT
  struct rlimit rl;

# ifdef RLIMIT_NOFILE
  if (!getrlimit (RLIMIT_NOFILE, &rl))
    max_fds = rl.rlim_max;
# endif

# ifdef RLIMIT_OFILE
  if (max_fds == -1 && !getrlimit (RLIMIT_OFILE, &rl))
    max_fds = rl.rlim_max;

# endif
#endif

#ifdef _SC_OPEN_MAX
  if (max_fds == -1)
    {
      long int scres = sysconf (_SC_OPEN_MAX);
      if (scres >= 0)
        max_fds = scres;
    }
#endif

#ifdef _POSIX_OPEN_MAX
  if (max_fds == -1)
    max_fds = _POSIX_OPEN_MAX;
#endif

#ifdef OPEN_MAX
  if (max_fds == -1)
    max_fds = OPEN_MAX;
#endif

  if (max_fds == -1)
    max_fds = 256;

  return max_fds;
}
