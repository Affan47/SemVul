Flush() {
  if (stdin_flags != -1) {
    fcntl(STDIN_FILENO, F_SETFL, stdin_flags & ~O_NONBLOCK);
  }

  if (stdout_flags != -1) {
    fcntl(STDOUT_FILENO, F_SETFL, stdout_flags & ~O_NONBLOCK);
  }

  fflush(stdout);
  fflush(stderr);
}
