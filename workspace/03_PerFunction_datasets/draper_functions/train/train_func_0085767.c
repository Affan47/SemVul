PTHREAD_DETACH(PTHREAD_T * pt) {
  pthread_t * handle;

  handle = pt->internal;
  GNUNET_ASSERT(handle != NULL);
  pthread_detach(*handle);
  pt->internal = NULL;
  FREE(handle);
  return;
}
