directory_list(char *dirname, Directory_list *dl)
{
  int n;
  struct stat sb;
  Vfs_handle *h;

  if (stat(dirname, &sb) == -1) {
	log_err((LOG_ERROR_LEVEL, "Can't stat %s", dirname));
	return(-1);
  }

  if ((sb.st_mode & S_IFMT) != S_IFDIR) {
	log_msg((LOG_WARN_LEVEL, "%s must be a directory", dirname));
	return(-1);
  }


  if (dl->dsv == NULL)
	dl->dsv = dsvec_init(NULL, sizeof(char *));

  if ((h = vfs_open_any(dirname)) == NULL) {
	log_msg((LOG_ERROR_LEVEL,
			 "Cannot open directory %s for listing", dirname));
	return(-1);
  }

  if ((n = vfs_list(h, NULL, NULL, directory_list_add, (void ***) dl)) == -1) {
	vfs_close(h);
	return(-1);
  }

  vfs_close(h);

  return(n);
}
