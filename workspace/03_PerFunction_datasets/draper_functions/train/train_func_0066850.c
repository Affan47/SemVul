UTF8FromLatin1(const char *s, int &len) {
	char *utfForm = new char[len*2+1];
	size_t lenU = 0;
	for (int i=0;i<len;i++) {
		unsigned int uch = static_cast<unsigned char>(s[i]);
		if (uch < 0x80) {
			utfForm[lenU++] = uch;
		} else {
			utfForm[lenU++] = static_cast<char>(0xC0 | (uch >> 6));
			utfForm[lenU++] = static_cast<char>(0x80 | (uch & 0x3f));
		}
	}
	utfForm[lenU] = '\0';
	len = lenU;
	return utfForm;
}
