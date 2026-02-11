parse_fragment(char *line, unsigned long size, struct patch *patch, struct fragment *fragment)
{
	int added, deleted;
	int len = linelen(line, size), offset;
	unsigned long oldlines, newlines;
	unsigned long leading, trailing;

	offset = parse_fragment_header(line, len, fragment);
	if (offset < 0)
		return -1;
	oldlines = fragment->oldlines;
	newlines = fragment->newlines;
	leading = 0;
	trailing = 0;


	line += len;
	size -= len;
	linenr++;
	added = deleted = 0;
	for (offset = len;
	     0 < size;
	     offset += len, size -= len, line += len, linenr++) {
		if (!oldlines && !newlines)
			break;
		len = linelen(line, size);
		if (!len || line[len-1] != '\n')
			return -1;
		switch (*line) {
		default:
			return -1;
		case '\n':
		case ' ':
			oldlines--;
			newlines--;
			if (!deleted && !added)
				leading++;
			trailing++;
			break;
		case '-':
			deleted++;
			oldlines--;
			trailing = 0;
			break;
		case '+':
			if (new_whitespace != nowarn_whitespace)
				check_whitespace(line, len);
			added++;
			newlines--;
			trailing = 0;
			break;


		case '\\':
			if (len < 12 || memcmp(line, "\\ ", 2))
				return -1;
			break;
		}
	}
	if (oldlines || newlines)
		return -1;
	fragment->leading = leading;
	fragment->trailing = trailing;


	if (12 < size && !memcmp(line, "\\ ", 2))
		offset += linelen(line, size);

	patch->lines_added += added;
	patch->lines_deleted += deleted;

	if (0 < patch->is_new && oldlines)
		return error("new file depends on old contents");
	if (0 < patch->is_delete && newlines)
		return error("deleted file still has contents");
	return offset;
}
