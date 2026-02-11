removedirectoryrecursively(const char *dirname)
  {

#ifndef _MSC_VER
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];

    if (path == NULL) {
      fprintf(stderr, "Out of memory error\n");
      return 0;
    }
    dir = opendir(dirname);
    if (dir == NULL) {
      perror("Error opendir()");
      return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
      if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
        snprintf(path, (size_t) PATH_MAX, "%s/%s", dirname, entry->d_name);
        if (entry->d_type == DT_DIR) {
          removedirectoryrecursively(path);
        }

        remove(path);


      }

    }
    closedir(dir);

    rmdir(dirname);


#else
	  std::cerr << "Remove dir not supposed" << std::endl;
#endif
    return 1;
  }
