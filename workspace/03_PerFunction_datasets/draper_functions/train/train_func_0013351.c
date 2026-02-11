nonhidden(const struct dirent *d) {
  if(*(d->d_name) == '.' && strcmp(d->d_name, "..") != 0) return 0;

  return 1;
}
