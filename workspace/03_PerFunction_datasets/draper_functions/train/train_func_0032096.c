sed(FILE *ip, int place)
{
	STATIC_STRBUF(sb);
	const char *parent_dir = (place == SUBDIR) ? "../.." : "..";
	int c, start_position = -1;

	strbuf_clear(sb);
	while ((c = fgetc(ip)) != EOF) {
		strbuf_putc(sb, c);
		if (c == '@') {
			int curpos = strbuf_getlen(sb);
			if (start_position == -1) {
				start_position = curpos - 1;
			} else {
				if (!strncmp("@PARENT_DIR@",
					strbuf_value(sb) + start_position,
					curpos - start_position))
				{
					strbuf_setlen(sb, start_position);
					strbuf_puts(sb, parent_dir);
					start_position = -1;
				} else {
					start_position = curpos - 1;
				}
			}
		} else if (!isalpha(c) && c != '_') {
			if (start_position != -1)
				start_position = -1;
		}
	}
	return strbuf_value(sb);
}
