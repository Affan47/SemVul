is_same_file(const char * file1, const char * file2) {
#ifdef _WIN32
#define FILECMP strcasecmp
#else
#define FILECMP strcmp
#endif
  if (FILECMP(file1, file2) == 0) {
    return 1;
  }

  char * canonical1 = make_canonical_path(file1);
  char * canonical2 = make_canonical_path(file2);
  int cmp = FILECMP(canonical1, canonical2);
  free(canonical1);
  free(canonical2);
  if (cmp == 0) {
    return 1;
  }

#ifndef _WIN32
  struct stat buf1;
  if (stat(file1, &buf1) == -1) {
    if (errno == ENOENT) {
      return 0;
    }
    else {
      fatal("cannot stat file: %s", file1);
    }
  }
  struct stat buf2;
  if (stat(file2, &buf2) == -1) {
    if (errno == ENOENT) {
      return 0;
    }
    else {
      fatal("cannot stat file: %s", file2);
    }
  }
  if (buf1.st_dev == buf2.st_dev &&
      buf1.st_ino == buf2.st_ino) {
    return 1;
  }
#endif
  return 0;
#undef FILECMP
}
