getcharset(int isclean)
{
	char *charset;

	if (isclean & (MIME_CTRLCHAR|MIME_HASNUL))
		charset = NULL;
	else if (isclean & MIME_HIGHBIT) {
		charset = (wantcharset && wantcharset != (char *)-1) ?
			wantcharset : value("charset");
		if (charset == NULL) {
			charset = defcharset;
		}
	} else {


		charset = value("charset7");
		if (charset == NULL) {
			charset = us_ascii;
		}
	}
	return charset;
}
