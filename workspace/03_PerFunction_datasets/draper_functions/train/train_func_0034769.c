getarcadiarombyname (const TCHAR *name)
{
	int i;
	for (i = 0; roms[i].name; i++) {
		if (roms[i].group == 0 && (roms[i].type == ROMTYPE_ARCADIAGAME || roms[i].type == ROMTYPE_ARCADIAGAME)) {
			TCHAR *p = roms[i].name;
			p = p + _tcslen (p) + 1;
			if (_tcslen (name) >= _tcslen (p) + 4) {
				const TCHAR *p2 = name + _tcslen (name) - _tcslen (p) - 4;
				if (!memcmp (p, p2, _tcslen (p)) && !memcmp (p2 + _tcslen (p2) - 4, ".zip", 4))
					return &roms[i];
			}
		}
	}
	return NULL;
}
