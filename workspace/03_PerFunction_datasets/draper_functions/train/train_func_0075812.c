read_binary_string(char **from, size_t len, const char *max)
{
	char *result;

	if (*from + len > max) {
		msg(MSG_CRITICAL,
		    "Attempt to read beyond end of file, corrupt file?\n");
		exit(EXIT_FAILURE);
	}

	result = xmalloc(len);
	memcpy(result, *from, len);
	*from += len;
	return result;
}
