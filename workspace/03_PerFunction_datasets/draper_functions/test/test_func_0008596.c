katoob_write(const char *file, const char *text, unsigned len, std::string& error) {
  int fd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644);
  if (fd == -1) {
    error = Utils::substitute("I can't create the file %s\n", file) + std::strerror(errno);
    return false;
  }

  ssize_t sz = write(fd, text, len);
  if (sz == -1) {
    error = Utils::substitute("I can't write to the file %s\n", file) + std::strerror(errno);
    close(fd);
    return false;
  }
  int x = close(fd);
  if (x == -1) {
    error = Utils::substitute("I can't close the file %s\n", file) + std::strerror(errno);
    return false;
  }
  return true;
}
