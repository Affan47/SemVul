Set() {
  if (!EnsureInitialized())
    return false;

  pthread_mutex_lock(&event_mutex_);
  event_status_ = true;
  pthread_cond_broadcast(&event_cond_);
  pthread_mutex_unlock(&event_mutex_);
  return true;
}
