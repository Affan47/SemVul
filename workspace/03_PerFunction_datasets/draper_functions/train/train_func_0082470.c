restore_line_number(void)
{
	char line[LINE_BUFFER_SIZE];
	if (skip_lines(rec_pos, line)) {
		if (ferror(word_file))
			pexit("fgets");
		fprintf(stderr, "fgets: Unexpected EOF\n");
		error();
	}
}
