load_tar(const char  *filename,
         const char  *name,
         cups_file_t *fp,
	 time_t      mtime,
	 off_t       size)
{
  char		curname[256],
		uri[1024];
  const char	*curext;
  struct stat	curinfo;
  off_t		next;


  (void)filename;

  add_ppd(name, name, "", "", "", "", "", "", mtime, size, 0,
          PPD_TYPE_ARCHIVE, "file");
  ChangedPPD = 1;


  while (read_tar(fp, curname, sizeof(curname), &curinfo))
  {
    next = cupsFileTell(fp) + ((curinfo.st_size + TAR_BLOCK - 1) &
                               ~(TAR_BLOCK - 1));

    if ((curext = strrchr(curname, '.')) != NULL &&
        !_cups_strcasecmp(curext, ".ppd"))
    {
      httpAssembleURIf(HTTP_URI_CODING_ALL, uri, sizeof(uri), "file", "", "",
                       0, "/%s/%s", name, curname);
      load_ppd(name, uri, "file", &curinfo, NULL, fp, next);
    }

    if (cupsFileTell(fp) != next)
      cupsFileSeek(fp, next);
  }

  return (1);
}
