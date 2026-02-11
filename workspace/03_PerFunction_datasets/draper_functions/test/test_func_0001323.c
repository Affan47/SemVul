assertFail(const char* assertion, const char* file,
                      unsigned int line) {
  debug("%1:%2: `%3' failed", file, line, assertion);
  if (abortAfterFailedAssertion) abort();
  return 0;
}
