fs_list(Vfs_handle *handle, int (*is_valid)(char *),
		int (*compar)(const void *, const void *),
		int (*add)(char *, char *, void ***), void ***names)
{
  int n;
  char *heir[2];
  FTS *ftsp;
  FTSENT *f;

  if (handle->sd->naming_context == NULL)
	heir[0] = "/";
  else
	heir[0] = handle->sd->naming_context;
  heir[1] = NULL;
  ftsp = fts_open(heir,
				  FTS_PHYSICAL | FTS_COMFOLLOW | FTS_NOCHDIR | FTS_XDEV,
				  (int (*)(const FTSENT **, const FTSENT **)) compar);
  if (ftsp == NULL) {
	handle->error_num = errno;
	handle->error_msg = strdup(strerror(errno));
	return(-1);
  }

  n = 0;
  while ((f = fts_read(ftsp)) != NULL) {
	if (f->fts_info == FTS_NS && f->fts_errno == ENOENT) {


	  continue;
	}

	if (f->fts_info == FTS_ERR
		|| f->fts_info == FTS_NS
		|| f->fts_info == FTS_DNR) {
	  errno = f->fts_errno;
	  handle->error_num = errno;
	  handle->error_msg = ds_xprintf("%s: %s", f->fts_path, strerror(errno));
	  return(-1);
	}
	if (f->fts_level > 0
		&& (f->fts_info == FTS_D || f->fts_info == FTS_DP)
		&& is_valid != NULL && is_valid(f->fts_name) != 1) {
	  if (fts_set(ftsp, f, FTS_SKIP) == -1) {
		handle->error_num = errno;
		handle->error_msg = ds_xprintf("%s: %s", f->fts_path, strerror(errno));
		return(-1);
	  }
	}
	else if (f->fts_info == FTS_F) {
	  if (add(handle->sd->naming_context, f->fts_path, names) == 1)
		n++;
	}
  }
  if (errno != 0) {
	errno = f->fts_errno;
	handle->error_num = errno;
	handle->error_msg = strdup(strerror(errno));
	return(-1);
  }

  if (fts_close(ftsp) == -1) {
	handle->error_num = errno;
	handle->error_msg = strdup(strerror(errno));
	return(-1);
  }

  return(n);
}
