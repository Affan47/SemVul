listDirectory(const char *dir, std::vector<File> &files, bool mediaOnly)
{
  if (!dir || !dir[0]) return;

  DIR *dp;
  struct dirent *dirp;
  char path[1024], ext[10];
  int len = strlen(dir);
  struct stat st;

  if (len > sizeof(path) - 2) {
    fprintf(stderr, "directory name too long: %s\n", dir);
    return;
  }

  strncpy(path, dir, sizeof(path)-2);
  if (dir[len-1] != '/') {
    strcat(path, "/");
    len++;
  }

  if((dp  = opendir(dir)) == NULL) {
    perror("listDirectory");
    return;
  }

  while ((dirp = readdir(dp)) != NULL) {
    if (dirp->d_name[0] != '.') {
      strncpy(path+len, dirp->d_name, sizeof(path)-len-1);
      stat(path, &st);
      extension(dirp->d_name, ext);
      if (S_ISDIR(st.st_mode) || !mediaOnly || isAudio(ext) || isVideo(ext))
	files.push_back(File(dirp->d_name, path, S_ISDIR(st.st_mode)));
    }
  }
  closedir(dp);
}
