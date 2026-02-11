do_touch(int argc, char **argv, char **result)
{
  int fd, st;
  char *file, *mode_str;
  mode_t mode;
  struct stat statb;

  file = argv[1];
  mode_str = argv[2];

  st = stat(file, &statb);
  if (st == -1) {
	if (errno != ENOENT) {
	  *result = strdup(strerror(errno));
	  return(-1);
	}

	if (mode_str == NULL)
	  mode = 0644;
	else if (abs_mode(mode_str, &mode) == -1) {
	  *result = "Invalid mode";
	  return(-1);
	}
	fd = open(file, O_WRONLY | O_CREAT, mode);
	if (fd == -1 || fstat(fd, &statb) != 0 || close(fd) != 0) {
	  *result = strdup(strerror(errno));
	  return(-1);
	}
  }
  else {

	if (utimes(file, NULL) == -1) {
	  *result = strdup(strerror(errno));
	  return(-1);
	}
  }

  return(0);
}
