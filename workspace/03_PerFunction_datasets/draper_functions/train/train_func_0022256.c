coverart_read_data(int cd_desc, struct art_data *art)
{
  DIR *coverart_dir;
  int index, coverart_fd;
  char root_dir[256], procbuffer[256], id[CDINDEX_ID_SIZE];
  struct stat st;
  struct dirent *d;

  if(getenv("HOME") == NULL) {
    strncpy(cddb_message, "$HOME is not set!", 256);
    return -1;
  }

  snprintf(root_dir, 256, "%s/.coverart", getenv("HOME"));
  cdindex_discid(cd_desc, id, CDINDEX_ID_SIZE);

  if(stat(root_dir, &st) < 0) {
    if(errno != ENOENT)
      return -1;
    else {
      art->art_present = 0;
      return 0;
    }
  } else if(!S_ISDIR(st.st_mode)) {
    errno = ENOTDIR;
    return -1;
  }

  if((coverart_dir = opendir(root_dir)) == NULL)
    return -1;

  while((d = readdir(coverart_dir)) != NULL) {
    if(strncmp(id, d->d_name, strlen(id) - 1) == 0) {
      strncpy(procbuffer, d->d_name, 256);
      index = strlen(d->d_name);
      if(strchr(d->d_name, '.') != NULL) {
	while(d->d_name[index--] != '.');
	index += 2;
	snprintf(art->art_mime_type, 16, "image/%s", d->d_name + index);
	art->art_mime_type[6 + (strlen(d->d_name) - index)] = '\0';
      } else
	art->art_mime_type[0] = '\0';

      snprintf(procbuffer, 256, "%s/%s", root_dir, d->d_name);
      if(stat(procbuffer, &st) < 0)
	return -1;

      art->art_length = st.st_size;
      if((coverart_fd = open(procbuffer, O_RDONLY)) < 0)
	return -1;

      if(read(coverart_fd, art->art_image, art->art_length) < 0)
	return -1;

      art->art_present = 1;

      return 0;
    }
  }

  art->art_present = 0;

  return 0;
}
