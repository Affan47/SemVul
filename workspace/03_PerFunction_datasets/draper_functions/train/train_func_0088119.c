fromUTF8(const char* str) {
	if (str != 0) {
		fromUTF8(str, strlen(str));
	}
}
