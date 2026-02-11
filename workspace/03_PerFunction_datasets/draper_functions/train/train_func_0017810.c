load_keyring (struct uae_prefs *p, const TCHAR *path)
{
	uae_u8 *keybuf;
	int keysize;
	TCHAR tmp[MAX_PATH], *d;
	int keyids[] = { 0, 48, 73, -1 };
	int cnt, i;

	free_keyring ();
	keybuf = target_load_keyfile (p, path, &keysize, tmp);
	addkey (keybuf, keysize, tmp);
	for (i = 0; keyids[i] >= 0; i++) {
		struct romdata *rd = getromdatabyid (keyids[i]);
		TCHAR *s;
		if (rd) {
			s = romlist_get (rd);
			if (s)
				addkeyfile (s);
		}
	}

	cnt = 0;
	for (;;) {
		keybuf = NULL;
		keysize = 0;
		tmp[0] = 0;
		switch (cnt)
		{
		case 0:
			if (path)
				_tcscpy (tmp, path);
			break;
		case 1:
			_tcscat (tmp, _T("rom.key"));
			break;
		case 2:
			if (p) {
				_tcscpy (tmp, p->path_rom.path[0]);
				_tcscat (tmp, _T("rom.key"));
			}
			break;
		case 3:
			_tcscpy (tmp, _T("roms/rom.key"));
			break;
		case 4:
			_tcscpy (tmp, start_path_data);
			_tcscat (tmp, _T("rom.key"));
			break;
		case 5:
			_stprintf (tmp, _T("%s../shared/rom/rom.key"), start_path_data);
			break;
		case 6:
			if (p) {
				for (i = 0; uae_archive_extensions[i]; i++) {
					if (_tcsstr (p->romfile, uae_archive_extensions[i]))
						break;
				}
				if (!uae_archive_extensions[i]) {
					_tcscpy (tmp, p->romfile);
					d = _tcsrchr (tmp, '/');
					if (!d)
						d = _tcsrchr (tmp, '\\');
					if (d)
						_tcscpy (d + 1, _T("rom.key"));
				}
			}
			break;
		case 7:
			return get_keyring ();
		}
		cnt++;
		if (!tmp[0])
			continue;
		addkeyfile (tmp);
	}
}
