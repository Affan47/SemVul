is_reg_file_for_access(const char *name, bool write_access)
{
  struct stat tmp;

  if (fc_stat(name, &tmp) == 0) {
    return S_ISREG(tmp.st_mode);
  } else {
    return write_access && errno == ENOENT;
  }
}
