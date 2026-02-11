bstr1 (uaecptr addr)
{
	static TCHAR bufx[257];
	static uae_char buf[257];
	int i;
	int n = get_byte (addr);
	addr++;

	for (i = 0; i < n; i++, addr++)
		buf[i] = get_byte (addr);
	buf[i] = 0;
	return au_fs_copy (bufx, sizeof (bufx) / sizeof (TCHAR), buf);
}
