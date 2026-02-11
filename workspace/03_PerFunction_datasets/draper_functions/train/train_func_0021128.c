packrat_find_file(const char * object, char * real_path, int path_size)
{
  Log(object)
  if (file_exists(object)) {
	strncpy(real_path,object,path_size);
	return 1;
  }

#ifndef AMIGA


  if (!strncasecmp("c:",object,2)) {
	char * path = getenv("PACKRAT_PATH");
	if (!path) path = getenv("PATH");
	if (path) {
	  char * saveptr;
	  char * chk;
	  path = strdup(path);
	  Log("Attempting rewrite using paths:");
	  Log(path);
	  chk = strtok_r(path,":",&saveptr);
	  do {
		snprintf(real_path,path_size,"%s/%s",chk, object + 2);
		if (file_exists(real_path) != 0) {
		  Log(" FOUND!");
		  free(path);
		  return 1;
		}
	  } while ((chk = strtok_r(0,":",&saveptr)));
	  free(path);
	}
  } else if (!strncasecmp("libs:",object,5)) {
	Log("libs: not yet rewritten");
  }
#endif


  return 0;
}
