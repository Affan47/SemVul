check_file_access(const char *path, char which, int mode) {
  if (!access(path, mode))
    return 1;

  fprintf(stderr,
	  "Check on %cPATH (%s) failed: %s\n"
	  "Please create this file and/or rerun `configure' "
	  "using --with-%cpath and recompile to correct this.\n",
	  which, path, strerror(errno), which);

  return 0;
}
