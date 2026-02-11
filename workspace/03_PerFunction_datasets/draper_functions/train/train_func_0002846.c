anthy_ask_scan(void (*request_scan)(struct textdict *, void *),
	       void *arg)
{
  DIR *dir;
  struct dirent *de;
  int size = 0;
  request_scan(anthy_private_text_dic, arg);
  request_scan(anthy_imported_text_dic, arg);
  dir = opendir(imported_dic_dir);
  if (!dir) {
    return ;
  }
  while ((de = readdir(dir))) {
    struct stat st_buf;
    struct textdict *td;
    char *fn = malloc(strlen(imported_dic_dir) +
		      strlen(de->d_name) + 3);
    if (!fn) {
      break;
    }
    sprintf(fn, "%s/%s", imported_dic_dir, de->d_name);
    if (stat(fn, &st_buf)) {
      free(fn);
      continue;
    }
    if (!S_ISREG(st_buf.st_mode)) {
      free(fn);
      continue;
    }
    size += st_buf.st_size;
    if (size > MAX_DICT_SIZE) {
      free(fn);
      break;
    }
    td = anthy_textdict_open(fn, 0);
    request_scan(td, arg);
    anthy_textdict_close(td);
    free(fn);
  }
  closedir(dir);
}
