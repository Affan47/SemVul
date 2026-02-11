zvolume_adddir_abs (struct zvolume *zv, struct zarchive_info *zai)
{
	struct znode *zn2;
	TCHAR *path = my_strdup (zai->name);
	TCHAR *p, *p2;
	int i;

	if (_tcslen (path) > 0) {

		TCHAR last;
		last = path[_tcslen (path) - 1];
		if (last == '/' || last == '\\')
			path[_tcslen (path) - 1] = 0;
	}
	zn2 = &zv->root;
	p = p2 = path;
	for (i = 0; path[i]; i++) {
		if (path[i] == '/' || path[i] == '\\') {
			path[i] = 0;
			zn2 = znode_adddir (zn2, p, zai);
			path[i] = FSDB_DIR_SEPARATOR;
			p = p2 = &path[i + 1];
		}
	}
	return znode_adddir (zn2, p, zai);
}
