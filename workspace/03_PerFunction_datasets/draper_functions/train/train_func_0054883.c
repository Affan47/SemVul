cab_convert_path_separator_2(struct cab *cab, struct archive_entry *entry)
{
	const wchar_t *wp;
	size_t i;


	if ((wp = archive_entry_pathname_w(entry)) != NULL) {
		archive_wstrcpy(&(cab->ws), wp);
		for (i = 0; i < archive_strlen(&(cab->ws)); i++) {
			if (cab->ws.s[i] == L'\\')
				cab->ws.s[i] = L'/';
		}
		archive_entry_copy_pathname_w(entry, cab->ws.s);
	}
}
