FormatLine(char* buffer, int bufsize,
                                 uint64 start, uint64 end, const char *flags,
                                 uint64 offset, int64 inode,
                                 const char *filename, dev_t dev) {

  char r = (flags && flags[0] == 'r') ? 'r' : '-';
  char w = (flags && flags[0] && flags[1] == 'w') ? 'w' : '-';
  char x = (flags && flags[0] && flags[1] && flags[2] == 'x') ? 'x' : '-';

  char p = (flags && flags[0] && flags[1] && flags[2] && flags[3] != 'p')
      ? '-' : 'p';

  const int rc = snprintf(buffer, bufsize,
                          "%08" PRIx64 "-%08" PRIx64 " %c%c%c%c %08" PRIx64 " %02x:%02x %-11" PRId64 " %s\n",
                          start, end, r,w,x,p, offset,
                          static_cast<int>(dev/256), static_cast<int>(dev%256),
                          inode, filename);
  return (rc < 0 || rc >= bufsize) ? 0 : rc;
}
