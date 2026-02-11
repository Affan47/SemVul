fwrite_string(gbfile* fd, const char* str)
{
  if (str && str[0]) {
    int len = strlen(str);
    fwrite_integer(fd, len);
    gbfwrite(str, 1, len, fd);
  } else {
    fwrite_integer(fd, 0);
  }
}
