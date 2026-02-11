zfile_fopenx2 (const TCHAR *name, const TCHAR *mode, int mask, int index)
{
	struct zfile *f;
	TCHAR tmp[MAX_DPATH];

#ifdef _WIN32
	if (isinternetfile (name))
		return zfile_fopen_internet (name, mode, mask);
#endif
	f = zfile_fopen_x (name, mode, mask, index);
	if (f)
		return f;
	if (_tcslen (name) <= 2)
		return NULL;
	if (name[1] != ':') {
		_tcscpy (tmp, start_path_data);
		_tcscat (tmp, name);
		f = zfile_fopen_x (tmp, mode, mask, index);
		if (f)
			return f;
	}
#if 0
	name += 2;
	if (name[0] == '/' || name[0] == '\\')
		name++;
	for (;;) {
		_tcscpy (tmp, start_path_data);
		_tcscpy (tmp, name);
		f = zfile_fopen_x (tmp, mode, mask);
		if (f)
			return f;
		while (name[0]) {
			name++;
			if (name[-1] == '/' || name[-1] == '\\')
				break;
		}
		if (name[0] == 0)
			break;
	}
#endif
	return NULL;
}
