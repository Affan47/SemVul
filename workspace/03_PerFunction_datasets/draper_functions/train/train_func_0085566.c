get_playlist_path(void)
{
  char *path = malloc(PATH_MAX);
  struct stat statbuf;


  strncpy(path, getenv("HOME"), PATH_MAX);
  strncat(path, "/" ECAPLAY_PLAYLIST_BASEDIR, PATH_MAX - strlen(path) - 1);


  if (stat(path, &statbuf) != 0) {
    printf("(ecaplay) Creating directory %s.\n", path);
    mkdir(path, 0700);
  }
  else {
    if (!S_ISDIR(statbuf.st_mode)) {

      free(path);
      path = NULL;
    }
  }

  if (path != NULL) {

    strncat(path, "/" ECAPLAY_PLAYLIST_FILE, PATH_MAX - strlen(path) - 1);
  }

  return path;
}
