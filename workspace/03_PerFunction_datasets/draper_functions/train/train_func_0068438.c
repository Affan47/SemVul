tor_lockfile_unlock(tor_lockfile_t *lockfile)
{
  tor_assert(lockfile);

  log_info(LD_FS, "Unlocking \"%s\"", lockfile->filename);
#ifdef _WIN32
  _lseek(lockfile->fd, 0, SEEK_SET);
  if (_locking(lockfile->fd, _LK_UNLCK, 1) < 0) {
    log_warn(LD_FS,"Error unlocking \"%s\": %s", lockfile->filename,
             strerror(errno));
  }
#elif defined(HAVE_FLOCK)
  if (flock(lockfile->fd, LOCK_UN) < 0) {
    log_warn(LD_FS, "Error unlocking \"%s\": %s", lockfile->filename,
             strerror(errno));
  }
#else

#endif

  close(lockfile->fd);
  lockfile->fd = -1;
  tor_free(lockfile->filename);
  tor_free(lockfile);
}
