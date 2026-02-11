uv__signal_unlock(void) {
  int r;
  char data = 42;

  do {
    r = write(uv__signal_lock_pipefd[1], &data, sizeof data);
  } while (r < 0 && errno == EINTR);

  return (r < 0) ? -1 : 0;
}
