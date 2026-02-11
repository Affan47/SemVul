init_pthreads() {
  if (dynamic_pthread_once == NULL) {
    dynamic_pthread_once =
        (pthread_once_func*) dlsym(RTLD_DEFAULT, "pthread_once");
  }

  if (dynamic_pthread_once == NULL || 1) {
    dynamic_pthread_once = &fake_pthread_once;
  }

  if (dynamic_pthread_mutex_lock == NULL) {
    dynamic_pthread_mutex_lock =
        (pthread_mutex_lock_func*) dlsym(RTLD_DEFAULT, "pthread_mutex_lock");
  }
  if (dynamic_pthread_mutex_lock == NULL) {
    dynamic_pthread_mutex_lock = &fake_pthread_mutex_lock;
  }

  if (dynamic_pthread_mutex_unlock == NULL) {
    dynamic_pthread_mutex_unlock =
        (pthread_mutex_unlock_func*) dlsym(RTLD_DEFAULT, "pthread_mutex_unlock");
  }
  if (dynamic_pthread_mutex_lock == NULL) {
    dynamic_pthread_mutex_lock = &fake_pthread_mutex_unlock;
  }
}
