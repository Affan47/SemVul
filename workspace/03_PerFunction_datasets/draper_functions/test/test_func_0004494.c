startup_open(const char *name)
{
  strid_t str;
  char *s;

  str = glkunix_stream_open_pathname((char *) name, fileusage_Data | fileusage_BinaryMode, 0);
  if(str) {
    set_game_filename(name);
    s = strrchr(name, '\\');
    if (!s) s = strrchr(name, '/');
    garglk_set_story_name(s ? s + 1 : name);
  } else {
    char *path = search_path;
    if(path) {
      char *p;
      char *newname = (char *) n_malloc(strlen(path) + strlen(name) + 2);
      path = n_strdup(path);
      for(p = n_strtok(path, ":"); p; p = n_strtok(NULL, ":")) {
	n_strcpy(newname, p);
	n_strcat(newname, "/");
	n_strcat(newname, name);
	str = glkunix_stream_open_pathname((char *) newname, fileusage_Data |
					   fileusage_BinaryMode, 0);
	if(str) {
	  set_game_filename(newname);
	  s = strrchr(newname, '\\');
	  if (!s) s = strrchr(newname, '/');
	  garglk_set_story_name(s ? s + 1 : newname);
	  break;
        }
      }
      n_free(path);
    }
  }

  if(!str)
    fprintf(stderr, "Cannot open '%s'\n", name);

  return str;
}
