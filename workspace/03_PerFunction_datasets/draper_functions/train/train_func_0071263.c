file_open(const char *file_name)
{
  fd_ = !strcmp(file_name, "-") ? ::dup(0) : ::open(file_name, O_RDONLY);
  open_error_ = strerror(errno);
}
