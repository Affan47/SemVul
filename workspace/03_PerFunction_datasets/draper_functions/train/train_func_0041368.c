processStream(const XML_Char *filename, XML_Parser parser)
{

  int fd = 0;

  if (filename != NULL) {
    fd = topen(filename, O_BINARY|O_RDONLY);
    if (fd < 0) {
      tperror(filename);
      return 0;
    }
  }
  for (;;) {
    int nread;
    char *buf = (char *)XML_GetBuffer(parser, READ_SIZE);
    if (!buf) {
      if (filename != NULL)
        close(fd);
      ftprintf(stderr, T("%s: out of memory\n"),
               filename != NULL ? filename : "xmlwf");
      return 0;
    }
    nread = read(fd, buf, READ_SIZE);
    if (nread < 0) {
      tperror(filename != NULL ? filename : "STDIN");
      if (filename != NULL)
        close(fd);
      return 0;
    }
    if (XML_ParseBuffer(parser, nread, nread == 0) == XML_STATUS_ERROR) {
      reportError(parser, filename != NULL ? filename : "STDIN");
      if (filename != NULL)
        close(fd);
      return 0;
    }
    if (nread == 0) {
      if (filename != NULL)
        close(fd);
      break;;
    }
  }
  return 1;
}
