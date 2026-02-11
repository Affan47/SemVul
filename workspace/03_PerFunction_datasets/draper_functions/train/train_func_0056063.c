memory_map_dump_2 (int log)
{
	bool imold;
	int i, j, max;
	addrbank *a1 = mem_banks[0];
	TCHAR txt[256];

	imold = currprefs.illegal_mem;
	currprefs.illegal_mem = false;
	max = currprefs.address_space_24 ? 256 : 65536;
	j = 0;
	for (i = 0; i < max + 1; i++) {
		addrbank *a2 = NULL;
		if (i < max)
			a2 = mem_banks[i];
		if (a1 != a2) {
			int k, mirrored, size, size_out;
			TCHAR size_ext;
			uae_u8 *caddr;
			const TCHAR *name;
			TCHAR tmp[MAX_DPATH];

			name = a1->name;
			if (name == NULL)
				name = _T("<none>");

			k = j;
			caddr = dump_xlate (k << 16);
			mirrored = caddr ? 1 : 0;
			k++;
			while (k < i && caddr) {
				if (dump_xlate (k << 16) == caddr)
					mirrored++;
				k++;
			}
			size = (i - j) << (16 - 10);
			size_out = size;
			size_ext = 'K';
			if (j >= 256) {
				size_out /= 1024;
				size_ext = 'M';
			}
			_stprintf (txt, _T("%08X %7d%c/%d = %7d%c %s"), j << 16, size_out, size_ext,
				mirrored, mirrored ? size_out / mirrored : size_out, size_ext, name);

			tmp[0] = 0;
			if (a1->flags == ABFLAG_ROM && mirrored) {
				TCHAR *p = txt + _tcslen (txt);
				uae_u32 crc = get_crc32 (a1->xlateaddr(j << 16), (size * 1024) / mirrored);
				struct romdata *rd = getromdatabycrc (crc);
				_stprintf (p, _T(" (%08X)"), crc);
				if (rd) {
					tmp[0] = '=';
					getromname (rd, tmp + 1);
					_tcscat (tmp, _T("\n"));
				}
			}
			_tcscat (txt, _T("\n"));
			if (log)
				write_log (_T("%s"),txt);
			else
				console_out (txt);
			if (tmp[0]) {
				if (log)
					write_log (_T("%s"),tmp);
				else
					console_out (tmp);
			}
			j = i;
			a1 = a2;
		}
	}
	currprefs.illegal_mem = imold;
}
