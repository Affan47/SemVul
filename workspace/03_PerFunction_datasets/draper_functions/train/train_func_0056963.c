TestOneNothrowNew(void* (*func)(size_t, const std::nothrow_t&)) {

  try {
    void* ptr = (*func)(kNotTooBig, std::nothrow);
    if (0 == ptr) {
      fprintf(LOGSTREAM, "allocation should not have failed.\n");
      abort();
    }
  } catch (...) {
    fprintf(LOGSTREAM, "allocation threw unexpected exception.\n");
    abort();
  }


  try {
    if ((*func)(kTooBig, std::nothrow) != 0) {
      fprintf(LOGSTREAM, "allocation should have failed.\n");
      abort();
    }
  } catch (...) {
    fprintf(LOGSTREAM, "nothrow allocation threw unexpected exception.\n");
    abort();
  }
}
