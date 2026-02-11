hts_debug_log_print(const char *format, ...) {
  if (hts_dgb_init > 0) {
    const int error = errno;
    FILE *const fp = hts_dgb_();
    va_list args;

    assertf(format != NULL);
    va_start(args, format);
    (void) vfprintf(fp, format, args);
    va_end(args);
    fputs("\n", fp);
    fflush(fp);
    errno = error;
  }
}
