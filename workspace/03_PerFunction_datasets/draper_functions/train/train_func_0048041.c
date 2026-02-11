AdjustBaseDir(const char* olddir, const char* newdir) {
  const char* old_path = GetPathName();
  if (old_path) {
    if (*old_path != '/') {
      if ((!olddir || !*olddir) && strcmp(newdir, "./") != 0) {
	char new_path[MAXPATHLEN];
	if (realpath(old_path, new_path))
	  SetPathName(new_path);
      } else if (olddir) {
	char whole_path[MAXPATHLEN];
	strcpy(whole_path, olddir);
	strcat(whole_path, "/");
	strcat(whole_path, old_path);
	char new_path[MAXPATHLEN];
	if (realpath(whole_path, new_path))
	  SetPathName(new_path);
      }
    }
  }
}
