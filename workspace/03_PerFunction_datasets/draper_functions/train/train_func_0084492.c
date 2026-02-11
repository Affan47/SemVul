parse_code(FILE *in, unsigned *line_count)
{
	char data[1024];
	struct answer **cur_line = lines;

	while (fgets(data, sizeof(data), in)) {
		int ret;
		(*line_count)++;
		if (!strcmp(data, "------END GEEK CODE BLOCK------\n"))
			return 0;
		if (!*cur_line)
			return ESYNTAX;
		if ((ret = process_line(*cur_line, data)))
			return ret;
		cur_line++;
	}
	return -1;
}
