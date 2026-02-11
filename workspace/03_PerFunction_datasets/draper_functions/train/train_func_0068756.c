set_line_info(int index, char *linepointer, char linelevel)
{
	if (index >= lines_info_alloc) {
		struct line_info *new_info;
		new_info = realloc(lines_info,
			(lines_info_alloc + REALLOC_CHUNK) * sizeof(struct line_info));
		if (!new_info)
			return -1;
		lines_info_alloc += REALLOC_CHUNK;
		lines_info = new_info;
	}

	lines_info[index].ptr = linepointer;
	lines_info[index].level = linelevel;
	return 0;
}
