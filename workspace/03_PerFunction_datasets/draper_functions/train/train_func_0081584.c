bstr_cut (Unit *unit, uaecptr addr)
{
	TCHAR *p = unit->tmpbuf3;
	int i, colon_seen = 0, off;
	int n = get_byte (addr);
	uae_char buf[257];

	off = 0;
	addr++;
	for (i = 0; i < n; i++, addr++) {
		uae_u8 c = get_byte (addr);
		buf[i] = c;
		if (c == '/' || (c == ':' && colon_seen++ == 0))
			off = i + 1;
	}
	buf[i] = 0;
	au_fs_copy (unit->tmpbuf3, sizeof (unit->tmpbuf3) / sizeof (TCHAR), buf);
	return &p[off];
}
