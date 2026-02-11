proc_lock_unset(Proc_lock *lock)
{

  if (lock == NULL)
	return(-1);

  if (lock->fd == -1)
	return(0);

  if (lock->type == F_ULOCK)
	return(0);
  if (lock->type != F_LOCK)
	return(-1);

  if (lockf(lock->fd, F_ULOCK, 0) == -1) {
	log_err((LOG_ERROR_LEVEL, "Could not unlock \"%s\"", lock->lock_file));
	return(-1);
  }
  lock->type = F_ULOCK;
  lock->fd = -1;

  return(0);
}
