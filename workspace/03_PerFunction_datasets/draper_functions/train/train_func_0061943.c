setup_directory(void)
{
  static int is_setup = 0;
  int r;
  if (is_setup) return;

#ifdef _WIN32
  {
    char buf[MAX_PATH];
    const char *tmp = buf;

    if (!GetTempPath(sizeof(buf),buf))
      tmp = "c:\\windows\\temp";
    tor_snprintf(temp_dir, sizeof(temp_dir),
                 "%s\\tor_test_%d", tmp, (int)getpid());
    r = mkdir(temp_dir);
  }
#else
  tor_snprintf(temp_dir, sizeof(temp_dir), "/tmp/tor_test_%d", (int) getpid());
  r = mkdir(temp_dir, 0700);
#endif
  if (r) {
    fprintf(stderr, "Can't create directory %s:", temp_dir);
    perror("");
    exit(1);
  }
  is_setup = 1;
  temp_dir_setup_in_pid = getpid();
}
