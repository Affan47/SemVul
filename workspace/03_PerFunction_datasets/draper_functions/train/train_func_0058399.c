getFileStream(const char* path, void **ptr, U32* fileSize)
{
  CONDITION cond;
  int fd;
  long bytesRead;
  unsigned char* p = 0;

  cond = UTL_FileSize(path, fileSize);
  if (cond != UTL_NORMAL) {
    COND_DumpConditions();
    exit(1);
  }

  *ptr = malloc(*fileSize);
  if (*ptr == NULL) {
    fprintf(stderr, "Could not malloc %d bytes; exiting.\n",
        *fileSize);
    exit(1);
  }
  p = (unsigned char*)*ptr;

  fd = open(path, O_RDONLY);
  if (fd <= 0) {
    fprintf(stderr, "Could not open file: %s\n", path);
    perror("");
    exit(1);
  }

  bytesRead = read(fd, *ptr, *fileSize);
  if (bytesRead != *fileSize) {
    fprintf(stderr, "Error reading file: %s, bytes read = %d\n",
        path, *fileSize);
    perror("");
    exit(1);
  }
  close(fd);
}
