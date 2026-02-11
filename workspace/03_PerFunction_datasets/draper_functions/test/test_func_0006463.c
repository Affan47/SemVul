smartypants_cb__dash(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
	if (size >= 3 && text[1] == '-' && text[2] == '-') {
		BUFPUTSL(ob, "&mdash;");
		return 2;
	}

	if (size >= 2 && text[1] == '-') {
		BUFPUTSL(ob, "&ndash;");
		return 1;
	}

	bufputc(ob, text[0]);
	return 0;
}
