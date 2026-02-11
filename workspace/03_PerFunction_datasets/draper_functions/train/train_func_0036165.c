bstr (Unit *unit, uaecptr addr)
{
	int i;
	int n = get_byte (addr);
	uae_char buf[257];

	addr++;
	for (i = 0; i < n; i++, addr++)
		buf[i] = get_byte (addr);
	buf[i] = 0;
	au_fs_copy (unit->tmpbuf3, sizeof (unit->tmpbuf3) / sizeof (TCHAR), buf);
	return unit->tmpbuf3;
}
