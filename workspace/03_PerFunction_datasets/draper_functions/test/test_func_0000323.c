cifs_strtoUTF16(__le16 *to, const char *from, int len,
	      const struct nls_table *codepage)
{
	int charlen;
	int i;
	wchar_t wchar_to;


	if (!strcmp(codepage->charset, "utf8")) {


		i  = utf8s_to_utf16s(from, len, UTF16_LITTLE_ENDIAN,
				       (wchar_t *) to, len);


		if (i >= 0)
			goto success;


	}

	for (i = 0; len && *from; i++, from += charlen, len -= charlen) {
		charlen = codepage->char2uni(from, len, &wchar_to);
		if (charlen < 1) {
			cifs_dbg(VFS, "strtoUTF16: char2uni of 0x%x returned %d\n",
				 *from, charlen);

			wchar_to = 0x003f;
			charlen = 1;
		}
		put_unaligned_le16(wchar_to, &to[i]);
	}

success:
	put_unaligned_le16(0, &to[i]);
	return i;
}
