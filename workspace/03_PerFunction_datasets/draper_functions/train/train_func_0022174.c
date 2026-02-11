string_expand_length(const char *line, int tabsize)
{
	size_t size, pos;

	for (pos = 0; line[pos]; pos++) {
		if (line[pos] == '\t' && tabsize > 0)
			size += tabsize - (size % tabsize);
		else
			size++;
	}
	return size;
}
