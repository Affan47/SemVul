FileError(char *fmt, ...) {
  va_list args;

  fprintf(stderr, "%s:%d: ", (inc_file?inc_file_name:input_file_name), lineno);
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
}
