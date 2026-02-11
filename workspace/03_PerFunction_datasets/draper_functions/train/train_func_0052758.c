kCheckFreeSpace(state_t *s, int funct_nr, int argc, reg_t *argv)
{
  char *path = kernel_dereference_char_pointer(s, argv[0], 0);
  char *testpath = (char*)sci_malloc(strlen(path) + 15);
  char buf[1024];
  int i;
  int fd;
  int failed = 0;
  int pathlen;

  strcpy(testpath, path);
  strcat(testpath, "freesci.foo");
  pathlen = strlen(testpath);

  while (IS_VALID_FD(fd = open(testpath, O_RDONLY))) {
    close(fd);
    if (testpath[pathlen - 2] == 'z') {
      SCIkwarn(SCIkWARNING, "Failed to find non-existing file for free space test\n");
      free(testpath);
      return NULL_REG;
    }


    if (testpath[pathlen - 1] == 'z') {
      testpath[pathlen - 1] = 'a';
      ++testpath[pathlen - 2];
    }
    else
      ++testpath[pathlen - 1];
  }

  fd = creat(testpath, 0600);

  if (!IS_VALID_FD(fd)) {
    SCIkwarn(SCIkWARNING,"Could not test for disk space: %s\n", strerror(errno));
    SCIkwarn(SCIkWARNING,"Test path was '%s'\n", testpath);
    free(testpath);
    return NULL_REG;
  }

  memset(buf, 0, sizeof(buf));
  for (i = 0; i < 1024; i++)
    if (write(fd, buf, 1024) < 1024)
      failed = 1;

  close(fd);

  remove(testpath);

  sci_free(testpath);

  return make_reg(0, !failed);
}
