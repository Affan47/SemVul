zfile_fopen_directory (const TCHAR *dirname)
{
	struct zvolume *zv = NULL;
	struct my_opendir_s *dir;
	TCHAR fname[MAX_DPATH];

	dir = my_opendir (dirname);
	if (!dir)
		return NULL;
	zv = zvolume_alloc_nofile (dirname, ArchiveFormatDIR, NULL, NULL);
	while (my_readdir (dir, fname)) {
		TCHAR fullname[MAX_DPATH];
		struct mystat statbuf;
		struct zarchive_info zai = { 0 };
		if (!_tcscmp (fname, _T(".")) || !_tcscmp (fname, _T("..")))
			continue;
		_tcscpy (fullname, dirname);
		_tcscat (fullname, FSDB_DIR_SEPARATOR_S);
		_tcscat (fullname, fname);
		if (!my_stat (fullname, &statbuf))
			continue;
		zai.name = fname;
		zai.size = statbuf.size;
		zai.tv.tv_sec = statbuf.mtime.tv_sec;
		zai.tv.tv_usec = statbuf.mtime.tv_usec;
		if (statbuf.mode & FILEFLAG_DIR) {
			zvolume_adddir_abs (zv, &zai);
		} else {
			struct znode *zn;
			zn = zvolume_addfile_abs (zv, &zai);

		}
	}
	my_closedir (dir);

	if (zv)
		zvolume_addtolist (zv);
	return zv;
}
