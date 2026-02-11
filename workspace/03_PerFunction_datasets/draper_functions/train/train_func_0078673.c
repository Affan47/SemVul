ay_utf8_to_str(const char *in)
{
	int i = 0;
	unsigned int n;
	char *result = NULL;

	if (in == NULL || *in == '\0')
		return "";

	result = ay_new(char, strlen(in) + 1);


	for (n = 0; n < strlen(in); n++) {
		unsigned char c = in[n];

		if (c < 128) {
			result[i++] = (char)c;
		} else {
			result[i++] = (c << 6) | (in[++n] & 63);
		}
	}
	result[i] = '\0';
	return result;
}
