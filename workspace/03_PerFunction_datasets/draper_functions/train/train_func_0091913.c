__thread_testcancel(_pthread_descr td) {
  int cancel=0;
  if (td && (td->cancelstate==PTHREAD_CANCEL_ENABLE)) cancel=td->canceled;
  if (cancel) __pthread_exit(PTHREAD_CANCELED);
}
