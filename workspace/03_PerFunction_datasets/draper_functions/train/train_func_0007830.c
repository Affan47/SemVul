glk_get_bin_line_stream(file_stream, buffer, max_length)
	strid_t         file_stream;
	char *			buffer;
	glui32			max_length;
{
	glsi32 character = 0;

	register int index = 0;

	character = glk_get_char_stream(file_stream);
	while (character != -1 && index < (int) max_length) {
		*(buffer + index) = (char) character;
		index++;
		if (character == (glsi32) '\n' ||
            character == (glsi32) '\r') {
			break;
		}
		character = glk_get_char_stream(file_stream);
	};

	*(buffer + index) = 0;

	return ((glui32) index);
}
