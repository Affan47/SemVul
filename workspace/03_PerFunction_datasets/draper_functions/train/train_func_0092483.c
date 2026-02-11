charset_new_length(int length,
	struct charset_header *header, FILE *file)
{
	int result;
	long offset;

	if ((result = length < CHARSET_LENGTH)) {
		putchar('.');
		fflush(stdout);

		if ((offset = ftell(file)) < 0) pexit("ftell");
		header->offsets[length][0] = offset;
		header->offsets[length][1] = offset >> 8;
		header->offsets[length][2] = offset >> 16;
		header->offsets[length][3] = offset >> 24;
	}

	return result;
}
