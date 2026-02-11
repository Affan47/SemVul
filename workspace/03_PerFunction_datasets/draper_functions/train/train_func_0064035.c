decode_utf8_byte(const string& sc, int len, int pos) {
	if (pos >= len) return -1;
	unsigned char ch = sc[pos];
	if ((ch & 0xC0) != 0x80) return -1;
	ch &= 0x3F;
	return ch;
}
