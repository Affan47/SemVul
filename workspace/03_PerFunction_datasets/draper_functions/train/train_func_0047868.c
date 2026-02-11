threadsafe_strerror(int errnum) {
  char *buf = (char *) malloc(STRERROR_BUFFER_SIZE);
  if(!buf) {
    fatal_error("Out of memory in threadsafe_strerror, errno", errnum);
  }
  THREADSAFE_STRERROR(errnum, buf, STRERROR_BUFFER_SIZE);
  return buf;
}
