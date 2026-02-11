getromdatabypath (const TCHAR *path)
{
	int i;
	for (i = 0; i < romlist_cnt; i++) {
		struct romdata *rd = rl[i].rd;
		if (rd->configname && path[0] == ':') {
			if (!_tcscmp(path + 1, rd->configname))
				return rd;
		}
		if (!_tcscmp(rl[i].path, path))
			return rl[i].rd;
	}
	return NULL;
}
