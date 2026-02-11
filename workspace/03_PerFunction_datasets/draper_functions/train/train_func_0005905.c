open_gpsbabel_inifile(void)
{
  char* name;
  char* envstr;
  gbfile* res = NULL;

  envstr = getenv("GPSBABELINI");
  if (envstr != NULL) {
    FILE* test;

    test = fopen(envstr, "r");
    if (test != NULL) {
      fclose(test);
      return gbfopen(envstr, "r", "GPSBabel");
    }
    warning("WARNING: GPSBabel-inifile, defined in environment, NOT found!\n");
    return NULL;
  }
  name = find_gpsbabel_inifile("");
  if (name == NULL) {
#ifdef __WIN32__
    name = find_gpsbabel_inifile(getenv("APPDATA"));
    if (name == NULL) {
      name = find_gpsbabel_inifile(getenv("WINDIR"));
    }
    if (name == NULL) {
      name = find_gpsbabel_inifile(getenv("SYSTEMROOT"));
    }
#else
    if ((envstr = getenv("HOME")) != NULL) {
      char* path;

      path = (char*) xmalloc(strlen(envstr) + 11);
      strcpy(path, envstr);
      strcat(path, "/.gpsbabel");
      name = find_gpsbabel_inifile(path);
      xfree(path);
    }
    if (name == NULL) {
      name = find_gpsbabel_inifile("/usr/local/etc");
    }
    if (name == NULL) {
      name = find_gpsbabel_inifile("/etc");
    }
#endif
  }
  if (name != NULL) {
    res = gbfopen(name, "r", "GPSBabel");
    if (gbinipathname) {
      xfree(gbinipathname);
    }
    gbinipathname = name;
  }
  return res;
}
