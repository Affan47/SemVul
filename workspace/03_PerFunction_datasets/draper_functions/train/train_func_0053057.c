dupAndToUpper(const char *str, QRencodeMode hint)
{
	char *newstr, *p;
	QRencodeMode mode;

	newstr = strdup(str);
	if(newstr == NULL) return NULL;

	p = newstr;
	while(*p != '\0') {
		mode = Split_identifyMode(p, hint);
		if(mode == QR_MODE_KANJI) {
			p += 2;
		} else {
			if (*p >= 'a' && *p <= 'z') {
				*p = (char)((int)*p - 32);
			}
			p++;
		}
	}

	return newstr;
}
