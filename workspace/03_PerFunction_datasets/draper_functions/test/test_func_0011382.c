message_show_helper(char *buf, enum msg_index_t first,
	enum msg_index_t last)
{
	size_t bufsize = PAGE_SIZE;
	char *buf_pointer = buf;
	int printed;
	enum msg_index_t cursor;
	int index = 0;
	*buf_pointer = '\0';

	for (cursor = first; cursor <= last; cursor++, index++) {
		if (bufsize <= 1)
			break;
		printed = scnprintf(buf_pointer, bufsize, "%d\t%s\n",
			index, spk_msg_get(cursor));
		buf_pointer += printed;
		bufsize -= printed;
	}

	return buf_pointer - buf;
}
