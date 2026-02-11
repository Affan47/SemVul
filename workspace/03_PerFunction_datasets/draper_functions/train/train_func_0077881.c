Split_identifyMode(const char *string, QRencodeMode hint)
{
	unsigned char c, d;
	unsigned int word;

	c = string[0];

	if(c == '\0') return QR_MODE_NUL;
	if(isdigit(c)) {
		return QR_MODE_NUM;
	} else if(isalnum(c)) {
		return QR_MODE_AN;
	} else if(hint == QR_MODE_KANJI) {
		d = string[1];
		if(d != '\0') {
			word = ((unsigned int)c << 8) | d;
			if((word >= 0x8140 && word <= 0x9ffc) || (word >= 0xe040 && word <= 0xebbf)) {
				return QR_MODE_KANJI;
			}
		}
	}

	return QR_MODE_8;
}
