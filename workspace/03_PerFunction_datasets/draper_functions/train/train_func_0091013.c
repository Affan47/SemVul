PTHREAD_JOIN(PTHREAD_T * pt,
		  void ** ret) {
  int k;
  pthread_t * handle;

  handle = pt->internal;
  GNUNET_ASSERT(handle != NULL);
  switch ((k=pthread_join(*handle, ret))) {
  case 0:
    FREE(handle);
    pt->internal = NULL;
    return;
  case ESRCH:
    abort();
  case EINVAL:
    abort();
  case EDEADLK:
    abort();
  default:
    abort();
  }
}
