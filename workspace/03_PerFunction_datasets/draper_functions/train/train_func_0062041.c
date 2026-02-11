read_next_char (FILE *file)


{
	char c;

	do {
		c = getc(file);
	} while (isspace(c));

	return (c);
}
