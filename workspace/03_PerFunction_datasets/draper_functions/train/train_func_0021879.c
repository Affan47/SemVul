CMbufTrim (char *buffer) {
	int i, len;

	if (buffer != (char *) NULL) {
		len = strlen (buffer);
		while ((len > 0) && (buffer [len - 1] == ' ')) {
			buffer [len - 1] = '\0';
			len--;
		}
		while ((len > 0) && (buffer [0] == ' ')) {
			for (i = 1;i < len; ++i) buffer [i - 1] = buffer [i];
			buffer [i - 1] = '\0';
			len--;
		}
	}
	return (buffer);
}
