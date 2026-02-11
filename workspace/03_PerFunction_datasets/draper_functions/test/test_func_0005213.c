fallback_stat(const char *name, struct stat *p, int prev_rv)
{


  switch (errno)
    {
    case ENOENT:
    case ENOTDIR:
      if (options.debug_options & DebugStat)
	fprintf(stderr, "fallback_stat(): stat(%s) failed; falling back on lstat()\n", name);
      return fstatat(state.cwd_dir_fd, name, p, AT_SYMLINK_NOFOLLOW);

    case EACCES:
    case EIO:
    case ELOOP:
    case ENAMETOOLONG:
#ifdef EOVERFLOW
    case EOVERFLOW:
#endif
    default:
      return prev_rv;
    }
}
