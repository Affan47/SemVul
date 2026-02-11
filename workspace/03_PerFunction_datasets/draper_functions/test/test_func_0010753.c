tty_append_printable_char(struct string_buf *buf, unsigned char c)
{
	if (c < 0x20 || c > 0x7E) {
		append_char(buf, '\\');
		append_char(buf, '0' + ((c >> 6) & 07));
		append_char(buf, '0' + ((c >> 3) & 07));
		append_char(buf, '0' + (c & 07));
	} else {
		if (c == '\\' || c ==  '"')
			append_char(buf, '\\');
		append_char(buf, c);
	}
}
