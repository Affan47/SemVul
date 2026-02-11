get_next_line(struct buffer *buff, char *line)
{
	char *p, *end_p;
	int count;

	if (buff->cursor >= buff->size)
	{
		return -1;
	}

	p = buff->space + buff->cursor;
	end_p = buff->space + buff->size;

	while (p < end_p && *p != '\n')
	{
		*line++ = *p++;
	}

	count =  p - buff->space - buff->cursor;
	buff->cursor += count + 1;

	*line = 0;

	return count;
}
