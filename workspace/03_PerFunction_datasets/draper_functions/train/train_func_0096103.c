LogToLocal(FILE *location, char *Format, ...)
{
  static char buffer[MAX_LOG_LINE_LENGTH];
  va_list argp;

  va_start(argp, Format);

  pal_vsnprintf(buffer, sizeof(buffer), Format, argp);

  va_end(argp);


  if (fprintf(location, "%s\n", buffer) < 0) {
    return 1;
  }

  return 0;
}
