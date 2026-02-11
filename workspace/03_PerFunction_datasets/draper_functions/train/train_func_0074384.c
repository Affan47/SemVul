WaitStopped() {
  if (!started_) return;
  int result = pthread_join(thread_, NULL);
  if (result != 0) {
    fprintf(stderr, "err code: %d %s\n", result, strerror(result));
  }
  started_ = false;
}
