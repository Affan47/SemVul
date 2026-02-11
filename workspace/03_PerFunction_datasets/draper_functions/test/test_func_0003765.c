load_svgs_file(void) {
#define BUFSIZE 1024
  char * result = NULL;
  int fd;
  char buf[BUFSIZE];
  int size = 0,ret;

  fd = open("testsvgs.xml",O_RDONLY);
  if (fd == -1) {
    WARN("Couldn't open test file");
    exit(-1);
  }
  while ((ret = read(fd,buf,BUFSIZE)) > 0) {
    result = realloc(result,size+ret);
    memcpy(result+size,buf,ret);
    size += ret;
  }
  if (ret < 0) {
    WARN("Reading from file failed: %s",strerror(errno));
    exit(-1);
  }
  close(fd);

  result = realloc(result,size+1);
  result[size] = '\0';
  return result;
}
