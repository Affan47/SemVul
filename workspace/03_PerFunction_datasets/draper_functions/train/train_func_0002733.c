create_parents(char *filename)
{
  char *p;

  p = filename;
  while (p && *p) {
    p = strchr(p + 1, '/');
    if (p) {
      *p = 0;
      if (mkdir(filename, 0777) && errno != EEXIST) {
	print_error("Cannot create directory %s: %s", filename,
		    strerror(errno));
	*p = '/';
	return 1;
      }
      *p = '/';
      p++;
    }
  }

  return 0;
}
