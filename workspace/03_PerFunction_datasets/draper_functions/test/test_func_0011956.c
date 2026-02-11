textbuffer_line_insert(TEXT_BUFFER_REC *buffer,
					LINE_REC *prev)
{
	LINE_REC *line;

	line = textbuffer_line_create(buffer);
	line->prev = prev;
	if (prev == NULL) {
		line->next = buffer->first_line;
                if (buffer->first_line != NULL)
			buffer->first_line->prev = line;
		buffer->first_line = line;
	} else {
		line->next = prev->next;
                if (line->next != NULL)
			line->next->prev = line;
		prev->next = line;
	}

	if (prev == buffer->cur_line)
		buffer->cur_line = line;
        buffer->lines_count++;

        return line;
}
