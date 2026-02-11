follow_path (
	DIR *dj,
	const TCHAR *path
)
{
	FRESULT res;
	BYTE *dir, ns;


#if _FS_RPATH
	if (*path == '/' || *path == '\\') {
		path++;	dj->sclust = 0;
	} else {
		dj->sclust = dj->fs->cdir;
	}
#else
	if (*path == '/' || *path == '\\')
		path++;
	dj->sclust = 0;
#endif

	if ((UINT)*path < ' ') {
		res = dir_sdi(dj, 0);
		dj->dir = 0;

	} else {
		for (;;) {
			res = create_name(dj, &path);
			if (res != FR_OK) break;
			res = dir_find(dj);
			ns = *(dj->fn+NS);
			if (res != FR_OK) {
				if (res != FR_NO_FILE) break;

				if (_FS_RPATH && (ns & NS_DOT)) {
					dj->sclust = 0; dj->dir = 0;
					res = FR_OK;
					if (!(ns & NS_LAST)) continue;
				} else {
					if (!(ns & NS_LAST)) res = FR_NO_PATH;
				}
				break;
			}
			if (ns & NS_LAST) break;
			dir = dj->dir;
			if (!(dir[DIR_Attr] & AM_DIR)) {
				res = FR_NO_PATH; break;
			}
			dj->sclust = LD_CLUST(dir);
		}
	}

	return res;
}
