zfile_fopen_archive_root (const TCHAR *filename, int flags)
{
	TCHAR path[MAX_DPATH], *p1, *p2, *lastp;
	struct zvolume *zv = NULL;

	int num, i;

	if (my_existsdir (filename))
		return zfile_fopen_directory (filename);

	num = 1;
	lastp = NULL;
	for (;;) {
		_tcscpy (path, filename);
		p1 = p2 = path;
		for (i = 0; i < num; i++) {
			while (*p1 != FSDB_DIR_SEPARATOR && *p1 != 0)
				p1++;
			if (*p1 == 0 && p1 == lastp)
				return NULL;
			if (i + 1 < num)
				p1++;
		}
		*p1 = 0;
		lastp = p1;
		if (my_existsfile (p2))
			return zfile_fopen_archive (p2, flags);
		num++;
	}

#if 0
	while (!last) {
		while (*p1 != FSDB_DIR_SEPARATOR && *p1 != 0)
			p1++;
		if (*p1 == 0)
			last = 1;
		*p1 = 0;
		if (!zv) {
			zv = zfile_fopen_archive (p2);
			if (!zv)
				return NULL;
		} else {
			struct znode *zn = get_znode (zv, p2);
			if (!zn)
				return NULL;
		}
		p2 = p1 + 1;
	}
	return zv;
#endif
}
