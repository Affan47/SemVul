next_line(FILE *fp, char **line, size_t *sz)
{
	while (first_line(fp, line, sz)) {
		if (!is_comment(*line))
			return 1;
	}
	return 0;
}
