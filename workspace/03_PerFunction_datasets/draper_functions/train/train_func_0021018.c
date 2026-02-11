strip_control_and_high(const char *input, char *buf, size_t buflen)
{
	char *bufptr = buf;
	for (; *input; input++) {
		if (*input < 32) {
			continue;
		}
		*bufptr++ = *input;
		if (bufptr == buf + buflen - 1) {
			break;
		}
	}
	*bufptr = '\0';
	return buf;
}
