strbuf_add_wrapped_text(struct strbuf *buf,
		const char *text, int indent, int indent2, int width)
{
	int w = indent, assume_utf8 = is_utf8(text);
	const char *bol = text, *space = NULL;

	if (width <= 0) {
		strbuf_add_indented_text(buf, text, indent, indent2);
		return 1;
	}

	if (indent < 0) {
		w = -indent;
		space = text;
	}

	for (;;) {
		char c;
		size_t skip;

		while ((skip = display_mode_esc_sequence_len(text)))
			text += skip;

		c = *text;
		if (!c || isspace(c)) {
			if (w < width || !space) {
				const char *start = bol;
				if (!c && text == start)
					return w;
				if (space)
					start = space;
				else
					print_spaces(buf, indent);
				strbuf_write(buf, start, text - start);
				if (!c)
					return w;
				space = text;
				if (c == '\t')
					w |= 0x07;
				else if (c == '\n') {
					space++;
					if (*space == '\n') {
						strbuf_write(buf, "\n", 1);
						goto new_line;
					}
					else if (!isalnum(*space))
						goto new_line;
					else
						strbuf_write(buf, " ", 1);
				}
				w++;
				text++;
			}
			else {
new_line:
				strbuf_write(buf, "\n", 1);
				text = bol = space + isspace(*space);
				space = NULL;
				w = indent = indent2;
			}
			continue;
		}
		if (assume_utf8)
			w += utf8_width(&text, NULL);
		else {
			w++;
			text++;
		}
	}
}
