ParseProcMapsLine(char *text, uint64 *start, uint64 *end,
                              char *flags, uint64 *offset,
                              int *major, int *minor, int64 *inode,
                              unsigned *filename_offset) {
#if defined(__linux__)


  char *endptr = text;
  if (endptr == NULL || *endptr == '\0')  return false;

  if (!StringToIntegerUntilCharWithCheck(start, endptr, 16, '-', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(end, endptr, 16, ' ', &endptr))
    return false;

  endptr = CopyStringUntilChar(endptr, 5, ' ', flags);
  if (endptr == NULL || *endptr == '\0')  return false;
  ++endptr;

  if (!StringToIntegerUntilCharWithCheck(offset, endptr, 16, ' ', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(major, endptr, 16, ':', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(minor, endptr, 16, ' ', &endptr))
    return false;

  if (!StringToIntegerUntilCharWithCheck(inode, endptr, 10, ' ', &endptr))
    return false;

  *filename_offset = (endptr - text);
  return true;
#else
  return false;
#endif
}
