exhcmd_edit(struct he_s *hedit, char *name)

{
  char *ab = alternate_buffer;
  struct passwd *pe;
  int new_buffer_f = 0;
  FILE *fp;
  char *skip, *p;
  char *path = 0;
  char *user = 0;
  int uid = getuid();

  skip = exh_skipcmd(name, p = (char *)alloca(strlen(name) + 1));
  util_trunc(name = p);
  while (*name == ' ' || *name == '\t') ++name;
  if (!strcmp(name, "#")) {
    if (he_alternate_buffer() < 0)
      he_message(0, "no alternate buffer");
    else {
      he_refresh_part(current_buffer->hedit, 0, -1);
      tio_ungetch('g' & 0x1f);
    }
    return skip;
  } else
    alternate_buffer = current_buffer->hedit->buffer_name;
  if (he_select_buffer(name) < 0) {
    new_buffer_f = 1;
    if (*name == '~') {
      user = strdup(name + 1);
      for (p = user; *p && *p != '/'; ++p);
      *p = 0;
      if (*user) {
        for (setpwent(); (pe = getpwent());)
          if (!strcmp(user, pe->pw_name)) break;
      } else
        for (setpwent(); (pe = getpwent());)
          if (uid == pe->pw_uid) break;
      if (pe) {
        path = (char *)malloc(strlen(name) + strlen(pe->pw_dir) + 4);
        strcpy(path, pe->pw_dir);
        strcat(path, name + strlen(user) + 1);
      } else
        path = name;
      free(user);
    } else
      path = name;
    if (!(fp = fopen(path, "r"))) {
      he_message(0, "@Abcan't open@~ `%s'", name);
      alternate_buffer = ab;
      if (path && path != name) free(path);
      return skip;
    } else {
      fclose(fp);
      he_open_buffer(name, path);
      he_select_buffer(name);
    }
  }
  he_status_message(!new_buffer_f);
  he_refresh_part(current_buffer->hedit, 0, -1);
  if (path && path != name) free(path);
  return skip;
}
