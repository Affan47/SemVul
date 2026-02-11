parsePseudoAttribute(const ENCODING *enc,
	const char *ptr,
	const char *end,
	const char **namePtr, const char **valPtr, const char **nextTokPtr)
{
	int c;
	char open;
	if (ptr == end) {
		*namePtr = 0;
		return 1;
	}
	if (!isSpace(toAscii(enc, ptr, end))) {
		*nextTokPtr = ptr;
		return 0;
	}
	do {
		ptr += enc->minBytesPerChar;
	} while (isSpace(toAscii(enc, ptr, end)));
	if (ptr == end) {
		*namePtr = 0;
		return 1;
	}
	*namePtr = ptr;
	for (;;) {
		c = toAscii(enc, ptr, end);
		if (c == -1) {
			*nextTokPtr = ptr;
			return 0;
		}
		if (c == '=')
			break;
		if (isSpace(c)) {
			do {
				ptr += enc->minBytesPerChar;
			} while (isSpace(c = toAscii(enc, ptr, end)));
			if (c != '=') {
				*nextTokPtr = ptr;
				return 0;
			}
			break;
		}
		ptr += enc->minBytesPerChar;
	}
	if (ptr == *namePtr) {
		*nextTokPtr = ptr;
		return 0;
	}
	ptr += enc->minBytesPerChar;
	c = toAscii(enc, ptr, end);
	while (isSpace(c)) {
		ptr += enc->minBytesPerChar;
		c = toAscii(enc, ptr, end);
	}
	if (c != '"' && c != '\'') {
		*nextTokPtr = ptr;
		return 0;
	}
	open = c;
	ptr += enc->minBytesPerChar;
	*valPtr = ptr;
	for (;; ptr += enc->minBytesPerChar) {
		c = toAscii(enc, ptr, end);
		if (c == open)
			break;
		if (!('a' <= c && c <= 'z')
			&& !('A' <= c && c <= 'Z')
			&& !('0' <= c && c <= '9')
			&& c != '.' && c != '-' && c != '_') {
			*nextTokPtr = ptr;
			return 0;
		}
	}
	*nextTokPtr = ptr + enc->minBytesPerChar;
	return 1;
}
